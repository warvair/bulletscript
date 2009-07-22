#ifndef __BS_BULLETMACHINE_H__
#define __BS_BULLETMACHINE_H__

#include <assert.h>
#include <map>
#include "bsBulletAffector.h"
#include "bsGunDefinitions.h"
#include "bsGun.h"

namespace BS_NMSP
{

	typedef std::vector<uint32> BytecodeBlock;

	class BulletGunBase;

	// Abstract class to provide a untemplated interface for AbstractSyntaxTree to use
	class _BSAPI BulletMachineBase
	{
	public:

		virtual bool createBulletAffector(const String& function) = 0;

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
	class BulletMachine : public BulletMachineBase
	{
		typedef std::vector<BulletAffector<BulletType>*> BulletAffectorList;
		BulletAffectorList mBulletAffectors;

		typedef std::map<String, typename BulletAffector<BulletType>::Function> FunctionMap;
		FunctionMap mFunctions;

	public:

		~BulletMachine()
		{
			// Delete BulletAffectors
			{
				typename BulletAffectorList::iterator it = mBulletAffectors.begin();
				while (it != mBulletAffectors.end())
				{
					delete (*it);
					++it;
				}
			}
		}

		bool createBulletAffector(const String& function)
		{
			if (mFunctions.find(function) == mFunctions.end())
				return false;

			typename BulletAffector<BulletType>::Function func = mFunctions[function];
			BulletAffector<BulletType>* aff = new BulletAffector<BulletType>(func);
			mBulletAffectors.push_back(aff);
			return true;
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

				typename BulletAffector<BulletType>::Argument& arg = 
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
			assert(affector >= 0 && affector < (int) mBulletAffectors.size() &&
				"BulletMachine::setBulletAffectorBytecode: out of bounds.");

			const typename BulletAffector<BulletType>::Argument& arg = 
				mBulletAffectors[affector]->getArgument(argument);
			
			codeSize = arg.record->byteCodeSize;
			return arg.record->byteCode;
		}

		void setBulletAffectorType(int affector, int argument, int type)
		{
			assert(affector >= 0 && affector < (int) mBulletAffectors.size () &&
				"BulletMachine::setBulletAffectorType: out of bounds.");

			typename BulletAffector<BulletType>::Argument& arg = 
				mBulletAffectors[affector]->getArgument (argument);

			arg.exprTypes |= type;
		}

		int getBulletAffectorType(int affector, int argument) const
		{
			assert(affector >= 0 && affector < (int) mBulletAffectors.size () &&
				"BulletMachine::getBulletAffectorType: out of bounds.");

			const typename BulletAffector<BulletType>::Argument& arg = 
				mBulletAffectors[affector]->getArgument (argument);
			
			return arg.exprTypes;
		}

		void setBulletAffectorValue(int affector, int argument, float value)
		{
			assert(affector >= 0 && affector < (int) mBulletAffectors.size () &&
				"BulletMachine::setBulletAffectorValue: out of bounds.");

			typename BulletAffector<BulletType>::Argument& arg = 
				mBulletAffectors[affector]->getArgument (argument);
			
			arg.value = value;
		}

		float getBulletAffectorValue(int affector, int argument) const
		{
			assert(affector >= 0 && affector < (int) mBulletAffectors.size () &&
				"BulletMachine::getBulletAffectorValue: out of bounds.");

			const typename BulletAffector<BulletType>::Argument& arg = 
				mBulletAffectors[affector]->getArgument(argument);
			
			return arg.value;
		}

		void registerAffectorListener(int affector,int argument, GlobalVariable* var)
		{
			assert(affector >= 0 && affector < (int) mBulletAffectors.size () &&
				"BulletMachine::registerAffectorListener: out of bounds.");

			typename BulletAffector<BulletType>::Argument& arg = 
				mBulletAffectors[affector]->getArgument(argument);

			var->registerAffectorArgument(&arg);
		}

		void updateAffectorInstances(int affector, float* arguments)
		{
			assert(affector >= 0 && affector < (int) mBulletAffectors.size() &&
				"BulletMachine::updateAffectorInstances: out of bounds.");

			mBulletAffectors[affector]->updateInstanceArguments(arguments);
		}

		void update()
		{
			// Only update if it has function calls
			typename BulletAffectorList::iterator it = mBulletAffectors.begin();
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

		void applyBulletAffectors(BulletGunBase* gun, BulletType& bullet, float frameTime)
		{
			for (int i = 0; i < gun->mNumAffectors; ++i)
				mBulletAffectors[gun->mAffectors[i].index]->runFunction(bullet, gun->mAffectors[i].arguments, frameTime);
		}

		bool registerAffectorFunction(const String& name, typename BulletAffector<BulletType>::Function func)
		{
			typename FunctionMap::iterator it = mFunctions.find(name);
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
