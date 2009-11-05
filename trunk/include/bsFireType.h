#ifndef __BS_FIRETYPE_H__
#define __BS_FIRETYPE_H__

#include "bsPrerequisites.h"
#include "bsBytecode.h"
#include "bsScriptStructs.h"
#include "bsParseTree.h"
#include "bsDeepMemoryPool.h"
#include "bsScriptMachine.h"

#if BS_PLATFORM == BS_PLATFORM_LINUX
#	include <string.h> // for memcpy
#endif

namespace BS_NMSP
{

	class FireTypeBase;

	struct FireTypeControl : public DeepMemoryPoolObject
	{
		// Scripted behaviour
		CodeRecord* code;
		ScriptState state;
		bstype* members; // Weak pointer to Gun members

		// Properties
		struct Property
		{
			float time;
			bstype speed;
		};

		Property properties[BS_MAX_PROPERTIES];
		uint32 activeProperties; // Bitfield for properties set

		// Affectors
		int numAffectors;
		int affectors[BS_MAX_FIRETYPE_AFFECTORS];

		// Internal
		FireTypeBase* __type;
		void* __object;			// Pointer to the current object that owns this FireTypeControl
		Gun* __gun;
		int __gunDef;			// GunDefinition index, for internal management

		FireTypeControl(int numLocals) :
			code(0),
			members(0),
			activeProperties(0),
			numAffectors(0),
			__type(0),
			__object(0),
			__gun(0),
			__gunDef(-1)
		{
			if (numLocals > 0)
				state.locals = new bstype[numLocals];
		}

		~FireTypeControl()
		{
			delete[] state.locals;
		}
	};

	class TypeManagerBase;

	class _BSAPI FireTypeBase
	{
	public:

		template<class A, class B, class C, class D> friend class TypeManager;

		DieFunction mDieFunction;

		// Member functions
		FireTypeBase(const String& name, int type, TypeManagerBase* typeMan, ScriptMachine* vm);

		virtual ~FireTypeBase()
		{
			mAffectors.clear();

			for (size_t i = 0; i < mAffectorInstances.size(); ++i)
				delete mAffectorInstances[i];

			mAffectorInstances.clear();
		}

		const String& getName() const;

		int getType() const;

		void setDieFunction(DieFunction func);

		bool registerProperty(const String& name, SetFunction set, GetFunction get);

		inline int getPropertyIndex(const String& name) const
		{
			for (int i = 0; i < mNumProperties; ++i)
			{
				if (mProperties[i].name == name)
					return i;
			}
			
			return -1;
		}

		void setProperty1(void* object, const String& prop, bstype value) const;

		void setProperty2(FireTypeControl* record, const String& prop, 
			bstype value, bstype time) const;

		bstype getProperty(void* object, const String& prop) const;

		virtual bool fireFunctionExists(const String& name) const = 0;

		bool affectorFunctionExists(const String& name) const
		{
			for (size_t i = 0; i < mAffectors.size(); ++i)
				if (mAffectors[i].name == name)
					return true;

			return false;
		}

		virtual int getNumFireFunctionArguments(const String& name) const = 0;

		virtual void generateBytecode(GunDefinition* def, ParseTreeNode* node,
			BytecodeBlock* code, const String& funcName) = 0;

		virtual int processCode(const uint32* code, ScriptState& state, Gun *gun, bstype x, 
			bstype y, bstype* members) = 0;

		void registerAffector(const String& name, AffectorFunction func)
		{
			AffectorEntry ae;
			ae.name = name;
			ae.func = func;

			mAffectors.push_back(ae);
		}

		AffectorFunction getAffectorFunction(const String& name)
		{
			for (size_t i = 0; i < mAffectors.size(); ++i)
			{
				if (mAffectors[i].name == name)
					return mAffectors[i].func;
			}

			return 0;
		}

		void createAffectorInstance(AffectorFunction func)
		{
			Affector* aff = new Affector(func, 1, false);
			// Set up
			// ...

			mAffectorInstances.push_back(aff);
		}

		void applyAffector(void* object, int index, float frameTime)
		{
			// should be object->__ft->__gun instead of 0
			// ...
			mAffectorInstances[index]->execute(object, frameTime, 0);
		}
	
	private:

		String mName;

	protected:

		int mType;

		TypeManagerBase* mTypeManager;

		ScriptMachine* mVM;
		
		// Properties
		struct Property
		{
			String name;
			SetFunction setter;
			GetFunction getter;

			Property() : setter(0), getter(0) {}
		};

		Property mProperties[BS_MAX_PROPERTIES];

		int mNumProperties;

		// Affectors
		struct AffectorEntry
		{
			String name;
			AffectorFunction func;
		};

		std::vector<AffectorEntry> mAffectors;

		std::vector<Affector*> mAffectorInstances;
	};

	template<class T>
	class FireType : public FireTypeBase
	{
	public:

		typedef T* (*FireFunction) (bstype, bstype, const bstype*);

		FireType(const String& name, int type, TypeManagerBase* typeMan, ScriptMachine* vm) : 
			FireTypeBase(name, type, typeMan, vm)
		{
		}

		~FireType()
		{
			mFunctions.clear();
		}

		bool fireFunctionExists(const String& name) const
		{
			for (size_t i = 0; i < mFunctions.size(); ++i)
				if (mFunctions[i].name == name)
					return true;

			return false;
		}

		/*
			[control function args]
			[emit function args]
			BC_FIRE
			FireType id
			FireType emit function id
			control function id + 1
			control function number of arguments
			number of affectors
			[affectors]
			GunDefinition id
		*/
		void generateBytecode(GunDefinition* def, ParseTreeNode* node,
							  BytecodeBlock* code, const String& funcName)
		{
			// opcode
			code->push_back(BC_FIRE);

			// type
			code->push_back((uint32) mType);

			// function id
			for (size_t i = 0; i < mFunctions.size(); ++i)
				if (mFunctions[i].name == funcName)
					code->push_back((uint32) i);

			// control type
			uint32 controlType = 0;
			int ftFuncIndex = -1;
			String callName = "";
			ParseTreeNode* tNode = node->getChild(3);
			if (tNode)
			{
				// See if we have controller function or affectors
				// ...

				if (tNode->getChild(0))
				{
					callName = tNode->getChild(0)->getStringData();

					// Get function index: +1 because 0 means no function
					ParseTree* tree = node->getTree();
					ftFuncIndex = tree->getCodeRecordIndex("Gun", def->getName(),
						"Function", callName);
				}
			}

			controlType = ftFuncIndex + 1;
			code->push_back(controlType);

			// Push number of FireType function arguments
			if (ftFuncIndex >= 0)
			{
				int defIndex = def->getFunctionIndex(callName);
				code->push_back(def->getFunction(defIndex).numArguments);
			}
			else
				code->push_back(0);

			// Push number of affectors: in this case we will hardcode it to 1
			int numAffectors = 1;
			code->push_back(numAffectors);
			for (int i = 0; i < numAffectors; ++i)
				code->push_back(0);
			
			// This is very hacky, but works.  This is because, at the point that this function is
			// called, the GunDefinition that is calling it will be the next to be added, and will
			// therefore have this index.  Terrible, I know.
			int index = mVM->getNumGunDefinitions(); 
			code->push_back((uint32) index);
		}

		int processCode(const uint32* code, ScriptState& state, Gun *gun, bstype x, bstype y, bstype* members)
		{
			int funcIndex = code[state.curInstruction + 2];
			uint32 numAffectors = 0;

			FireFunction func = mFunctions[funcIndex].func;

			T* type = func(x, y, &state.stack[state.stackHead]);
			state.stackHead -= mFunctions[funcIndex].numArguments;

			if (type)
			{
				// If specified, set up control stuff
				uint32 controlFunc = code[state.curInstruction + 3];
				numAffectors = code[state.curInstruction + 5];

				// Should create FireTypeControl if it uses a controller function,
				// or affectors.
				if (controlFunc == 0 && numAffectors == 0)
				{
					type->__ft = 0;
				}
				else
				{
					// Request a FireTypeControl from pool
					int gunDef = code[state.curInstruction + 6 + numAffectors];
					type->__ft = mVM->getFireTypeRecord(gunDef);
					type->__ft->__type = this;
					type->__ft->__gun = gun;

					// Set up control function
					if (controlFunc != 0)
					{
						int numArgs = code[state.curInstruction + 4];

						type->__ft->code = mVM->getCodeRecord(controlFunc - 1);
						type->__ft->members = members;
						
						state.stackHead -= numArgs;
						memcpy(type->__ft->state.locals, state.stack + state.stackHead, numArgs * sizeof(bstype));
					}
					
					// Set up affectors
					type->__ft->numAffectors = numAffectors;
					for (uint32 i = 0; i < numAffectors; ++i)
						type->__ft->affectors[i] = (int) code[state.curInstruction + 6 + i];
				}
			}

			return 7 + numAffectors; // this must match the number of bytecodes emitted in generateBytecode
		}

		void registerFireFunction(const String& name, int numArgs, FireFunction func)
		{
			FunctionEntry fe;
			fe.name = name;
			fe.func = func;
			fe.numArguments = numArgs;

			mFunctions.push_back(fe);
		}

		int getNumFireFunctionArguments(const String& name) const
		{
			for (size_t i = 0; i < mFunctions.size(); ++i)
				if (mFunctions[i].name == name)
					return mFunctions[i].numArguments;

			return -1;
		}

	private:

		// Functions
		struct FunctionEntry
		{
			String name;
			FireFunction func;
			int numArguments;
		};

		std::vector<FunctionEntry> mFunctions;

	};

}

#endif
