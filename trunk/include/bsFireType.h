#ifndef __BS_FIRETYPE_H__
#define __BS_FIRETYPE_H__

#include "bsPrerequisites.h"
#include "bsBytecode.h"
#include "bsScriptStructs.h"
#include "bsParseTree.h"
#include "bsDeepMemoryPool.h"
#include "bsScriptMachine.h"

#if BS_PLATFORM == BS_PLATFORM_LINUX
#include <string.h> // for memcpy
#endif

namespace BS_NMSP
{
	enum
	{
		FTF_AnchorPosition		= (1 << 1),
		FTF_AnchorRotation		= (1 << 2),
		FTF_FunctionOffset		= (1 << 8),
	};

	class FireTypeBase;

	struct FireTypeScriptRecord : public DeepMemoryPoolObject
	{
		CodeRecord* code;

		ScriptState state;

		// Pointer to the FireType instance, currently stored in ScriptMachine
		FireTypeBase* type;

		// Pointer to the current object that owns this FireTypeScriptRecord
		void* object;

		struct Property
		{
			float time;
			bstype speed;
		};

		Property properties[BS_MAX_PROPERTIES];

		// bitfield for set properties
		uint32 activeProperties; 

		// Fields for anchoring, etc, misc flags
		uint32 flags;

		// Weak pointer to Gun members
		bstype* members;

		// GunDefinition index, for internal management
		int __gunDef;

		FireTypeScriptRecord(int numLocals) :
			code(0),
			type(0),
			object(0),
			activeProperties(0),
			flags(0),
			__gunDef(-1),
			members(0)
		{
			if (numLocals > 0)
				state.locals = new bstype[numLocals];
		}

		~FireTypeScriptRecord()
		{
			delete[] state.locals;
		}
	};

	class TypeManagerBase;

	class _BSAPI FireTypeBase
	{
	public:

		template<class A, class B, class C> friend class TypeManager;

		typedef void (*DieFunction) (void*);

		typedef void (*SetFunction) (void*, bstype);

		typedef bstype (*GetFunction) (void*);

		DieFunction mDieFunction;

		FireTypeBase(const String& name, int type, TypeManagerBase* typeMan, ScriptMachine* vm);

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

		void setProperty2(FireTypeScriptRecord* record, const String& prop, 
			bstype value, bstype time) const;

		bstype getProperty(void* object, const String& prop) const;

		virtual bool fireFunctionExists(const String& name) const = 0;

		virtual int getNumFireFunctionArguments(const String& name) const = 0;

		virtual void generateBytecode(GunDefinition* def, ParseTreeNode* node,
			BytecodeBlock* code, const String& funcName) = 0;

		virtual int processCode(const uint32* code, ScriptState& state, bstype x, bstype y,
			bstype* members) = 0;
	
	private:

		String mName;

	protected:

		int mType;

		TypeManagerBase* mTypeManager;

		ScriptMachine* mVM;
		
		struct Property
		{
			String name;
			SetFunction setter;
			GetFunction getter;

			Property() : setter(0), getter(0) {}
		};

		Property mProperties[BS_MAX_PROPERTIES];

		int mNumProperties;
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
			ParseTreeNode* tNode = node->getChild(3);
			if (tNode)
			{
				ParseTreeNode* aNode = tNode->getChild(0);
				String callName = aNode->getChild(0)->getStringData();

				// Get function index: +1 because 0 means no function
				ParseTree* tree = node->getTree();
				ftFuncIndex = tree->getCodeRecordIndex("Gun", def->getName(),
					"Function", callName);

				controlType |= (ftFuncIndex + 1) * FTF_FunctionOffset;

				aNode = tNode->getChild(1);
				if (aNode)
				{
					String anchors = aNode->getStringData();
					for (size_t i = 0; i < anchors.length(); ++i)
					{
						if (anchors[i] == 'R')
							controlType |= FTF_AnchorRotation;
						else if (anchors[i] == 'P')
							controlType |= FTF_AnchorPosition;
					}
				}
			}

			code->push_back(controlType);

			// Push number of FireType function arguments
			if (ftFuncIndex >= 0)
				code->push_back(def->getFunction(ftFuncIndex).numArguments);
			else
				code->push_back(0);
			
			// This is very hacky, but works.  This is because, at the point that this function is
			// called, the gun that is calling it will be the next to be added, and will therefore
			// have this index.  Terrible, I know.
			int index = mVM->getNumGunDefinitions(); 
			code->push_back((uint32) index);
		}

		int processCode(const uint32* code, ScriptState& state, bstype x, bstype y, bstype* members)
		{
			int funcIndex = code[state.curInstruction + 2];
			FireFunction func = mFunctions[funcIndex].func;

			T* type = func(x, y, &state.stack[state.stackHead]);

			state.stackHead -= mFunctions[funcIndex].numArguments;

			// If specified, set up control stuff
			uint32 control = code[state.curInstruction + 3];
			if (control == 0)
			{
				type->__ft = 0;
			}
			else
			{
				// Request a FireTypeScriptRecord from pool
				int gunDef = code[state.curInstruction + 5];
				type->__ft = mVM->getFireTypeRecord(gunDef);
				type->__ft->type = this;
				type->__ft->__gunDef = gunDef;
				type->__ft->members = members;
				type->__ft->flags |= control;

				uint32 ftFunc = control >> 8;
				if (ftFunc > 0)
				{
					type->__ft->code = mVM->getCodeRecord(ftFunc - 1);

					int numArgs = code[state.curInstruction + 4];
					
					state.stackHead -= numArgs;
					memcpy(type->__ft->state.locals, state.stack + state.stackHead, numArgs * sizeof(bstype));
				}
			}
	
			return 6; // this must match the number of bytecodes emitted in generateBytecode
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
