#ifndef __SH_BULLETMACHINE_H__
#define __SH_BULLETMACHINE_H__

#include <map>
#include <assert.h>
#include "shPrerequisites.h"
#include "shBulletAffector.h"
#include "shScriptDefinition.h"

namespace Shmuppet
{

	typedef std::vector<uint32> BytecodeBlock;

	// Abstract class to provide a untemplated interface for AbstractSyntaxTree to use
	class _ShmuppetAPI BulletMachineBase
	{
	public:

		virtual bool addGunDefinition(const String &name, 
			GunDefinition* def) = 0;

		virtual GunDefinition* getGunDefinition(const String &name) = 0;
		
		virtual void createBulletAffector(const String& function) = 0;

		virtual int getNumBulletAffectors() const = 0;

		virtual void addBulletAffectorArgument(ScriptMachine* machine) = 0;

		virtual void setBulletAffectorBytecode(int affector, 
			int argument, const BytecodeBlock& bytecode) = 0;

		virtual const uint32* getBulletAffectorBytecode(int affector, int argument, 
			size_t& codeSize) const = 0;

		virtual void setBulletAffectorType(int affector, int argument, int type) = 0;

		virtual int getBulletAffectorType(int affector, int argument) const = 0;

		virtual void setBulletAffectorValue(int affector, int argument, float value) = 0;

		virtual float getBulletAffectorValue(int affector, int argument) const = 0;

		virtual void registerAffectorListener(int affector, int argument, GlobalVariable *var) = 0;

		virtual bool affectorFunctionExists(const String& name) const = 0;

	};

	template <typename BulletType>
	class _ShmuppetAPI BulletMachine : public BulletMachineBase
	{
		typedef std::map<String, GunDefinition*> GunDefinitionMap;
		GunDefinitionMap mDefinitions;

		typedef std::vector<BulletAffector<BulletType>*> BulletAffectorList;
		BulletAffectorList mBulletAffectors;

		typedef std::map<String, typename BulletAffector<BulletType>::Function> FunctionMap;
		FunctionMap mFunctions;

	public:

		~BulletMachine()
		{
			// Delete GunDefinitions
			{
				GunDefinitionMap::iterator it = mDefinitions.begin();
				while (it != mDefinitions.end())
				{
					delete it->second;
					++it;
				}
			}

			// Delete BulletAffectors
			{
				BulletAffectorList::iterator it = mBulletAffectors.begin();
				while (it != mBulletAffectors.end())
				{
					delete (*it);
					++it;
				}
			}
		}

		bool addGunDefinition(const String& name, GunDefinition* def)
		{
			// Todo: check to make sure it already doesn't exist
			GunDefinitionMap::iterator it = mDefinitions.find(name);
			if (it != mDefinitions.end())
				return false;

			mDefinitions[name] = def;
			return true;
		}

		GunDefinition *getGunDefinition(const String& name)
		{
			GunDefinitionMap::iterator it = mDefinitions.find(name);
			if (it == mDefinitions.end())
			{
				return 0;
			}
			else
			{
				return it->second;
			}
		}

		void createBulletAffector(const String& function)
		{
			// Todo: make sure that mFunctions[function] exists
			// ...
			BulletAffector<BulletType>::Function func = mFunctions[function];
			BulletAffector<BulletType>* aff = new BulletAffector<BulletType>(func);
			mBulletAffectors.push_back(aff);
		}

		BulletAffector<BulletType>* getBulletAffector(int index)
		{
			assert(index >= 0 && index < (int) mBulletAffectors.size () &&
				"BulletMachine::getBulletAffector: out of bounds.");
			return mBulletAffectors[index];
		}

		int getNumBulletAffectors() const
		{
			return (int) mBulletAffectors.size();
		}

		void addBulletAffectorArgument(ScriptMachine* machine)
		{
			int index = getNumBulletAffectors() - 1;
			assert(index >= 0 && index < (int) mBulletAffectors.size () &&
				"BulletMachine::addBulletAffectorArgument: out of bounds.");
			mBulletAffectors[index]->addArgument(machine);
		}

		void setBulletAffectorBytecode(int affector, int argument, const BytecodeBlock &bytecode)
		{
			if (bytecode.size() > 0)
			{
				assert(affector >= 0 && affector < (int) mBulletAffectors.size () &&
					"BulletMachine::setBulletAffectorBytecode: out of bounds.");

				BulletAffector<BulletType>::Argument& arg = 
					mBulletAffectors[affector]->getArgument(argument);

				arg.record = new CodeRecord;
				arg.record->byteCodeSize = (uint32) bytecode.size();
				arg.record->byteCode = new uint32[arg.record->byteCodeSize];
				for (uint32 i = 0; i < arg.record->byteCodeSize; ++i)
					arg.record->byteCode[i] = bytecode[i];
			}
		}

		const uint32 *getBulletAffectorBytecode(int affector, int argument, size_t& codeSize) const
		{
			assert(affector >= 0 && affector < (int) mBulletAffectors.size () &&
				"BulletMachine::setBulletAffectorBytecode: out of bounds.");

			const BulletAffector<BulletType>::Argument& arg = 
				mBulletAffectors[affector]->getArgument (argument);
			
			codeSize = arg.record->byteCodeSize;
			return arg.record->byteCode;
		}

		void setBulletAffectorType(int affector, int argument, int type)
		{
			assert(affector >= 0 && affector < (int) mBulletAffectors.size () &&
				"BulletMachine::setBulletAffectorType: out of bounds.");

			BulletAffector<BulletType>::Argument& arg = 
				mBulletAffectors[affector]->getArgument (argument);

			arg.exprTypes |= type;
		}

		int getBulletAffectorType(int affector, int argument) const
		{
			assert(affector >= 0 && affector < (int) mBulletAffectors.size () &&
				"BulletMachine::getBulletAffectorType: out of bounds.");

			const BulletAffector<BulletType>::Argument& arg = 
				mBulletAffectors[affector]->getArgument (argument);
			
			return arg.exprTypes;
		}

		void setBulletAffectorValue(int affector, int argument, float value)
		{
			assert(affector >= 0 && affector < (int) mBulletAffectors.size () &&
				"BulletMachine::setBulletAffectorValue: out of bounds.");

			BulletAffector<BulletType>::Argument& arg = 
				mBulletAffectors[affector]->getArgument (argument);
			
			arg.value = value;
		}

		float getBulletAffectorValue(int affector, int argument) const
		{
			assert(affector >= 0 && affector < (int) mBulletAffectors.size () &&
				"BulletMachine::getBulletAffectorValue: out of bounds.");

			const BulletAffector<BulletType>::Argument& arg = 
				mBulletAffectors[affector]->getArgument (argument);
			
			return arg.value;
		}

		void registerAffectorListener(int affector,int argument, GlobalVariable* var)
		{
			assert(affector >= 0 && affector < (int) mBulletAffectors.size () &&
				"BulletMachine::registerAffectorListener: out of bounds.");

			BulletAffector<BulletType>::Argument& arg = 
				mBulletAffectors[affector]->getArgument (argument);

			var->registerAffectorArgument(&arg);
		}

		void updateAffectorInstances(int affector, float* arguments)
		{
			assert(affector >= 0 && affector < (int) mBulletAffectors.size () &&
				"BulletMachine::updateAffectorInstances: out of bounds.");

			mBulletAffectors[affector]->updateInstanceArguments (arguments);
		}

		void updateBulletAffectors()
		{
			// Only update if it has function calls
			BulletAffectorList::iterator it = mBulletAffectors.begin();
			while (it != mBulletAffectors.end())
			{
				(*it)->updateFunctionArguments();
				++it;
			}
		}

		void updateInstanceArguments(int index, float* arguments, const GunScriptRecord& gunRecord)
		{
			mBulletAffectors[index]->updateInstanceArguments(arguments, gunRecord);
		}

		void applyBulletAffectors(GunBase* gun, BulletType& bullet, float frameTime)
		{
			GunBase::AffectorList::iterator it = gun->mAffectors.begin();
			while (it != gun->mAffectors.end())
			{
				GunBase::Affector& aff = *it;
				mBulletAffectors[aff.index]->runFunction(bullet, aff.arguments, frameTime);
				++it;
			}			
		}

		bool registerAffectorFunction(const String& name, 
			typename BulletAffector<BulletType>::Function func)
		{
			FunctionMap::iterator it = mFunctions.find(name);
			if (it != mFunctions.end())
				return false;

			mFunctions[name] = func;
			return true;
		}

		bool affectorFunctionExists(const String& name) const
		{
			return (mFunctions.find(name) != mFunctions.end());			
		}

	};

}
#endif
