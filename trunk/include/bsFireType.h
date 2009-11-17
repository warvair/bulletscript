#ifndef __BS_FIRETYPE_H__
#define __BS_FIRETYPE_H__

#include "bsPrerequisites.h"
#include "bsBytecode.h"
#include "bsCore.h"
#include "bsEmitter.h"
#include "bsParseTree.h"
#include "bsDeepMemoryPool.h"

#if BS_PLATFORM == BS_PLATFORM_LINUX
#	include <string.h> // for memcpy
#endif

namespace BS_NMSP
{

	class FireType;

	struct FireTypeControl : public DeepMemoryPoolObject
	{
		// Scripted behaviour
		CodeRecord* code;
		ScriptState state;

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
		int affectors[BS_MAX_EMITTER_AFFECTORS];

		// Internal
		FireType* __type;
		UserTypeBase* __object;	// Pointer to the current object that owns this FireTypeControl
		int __emitterDefinition;			// EmitterDefinition index

		FireTypeControl(int numLocals) :
			code(0),
			activeProperties(0),
			numAffectors(0),
			__type(0),
			__object(0),
			__emitterDefinition(-1)
		{
			if (numLocals > 0)
				state.locals = new bstype[numLocals];
		}

		~FireTypeControl()
		{
			delete[] state.locals;
		}
	};

	class ScriptMachine;
	class TypeManager;

	class _BSAPI FireType
	{
	public:

		friend class TypeManager;

		DieFunction mDieFunction;

		// Member functions
		FireType(const String& name, int type, TypeManager* typeMan, ScriptMachine* vm);

		~FireType();

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

		void setProperty1(FireTypeControl* record, const String& prop, bstype value) const;

		void setProperty2(FireTypeControl* record, const String& prop, 
			bstype value, bstype time) const;

		bstype getProperty(UserTypeBase* object, const String& prop) const;

		void registerFireFunction(const String& name, int numArgs, FireFunction func);
		
		bool fireFunctionExists(const String& name) const;

		bool affectorFunctionExists(const String& name) const;

		int getNumFireFunctionArguments(const String& name) const;

		void getControllers(EmitterDefinition* def, ParseTreeNode* node,
			String& callName, int& funcIndex, std::vector<int>& affectors);

		void generateBytecode(EmitterDefinition* def, ParseTreeNode* node,
			BytecodeBlock* code, const String& funcName);

#ifdef BS_Z_DIMENSION
		int processCode(const uint32* code, ScriptState& state, bstype x, 
			bstype y, bstype z, bstype* members);
#else
		int processCode(const uint32* code, ScriptState& state, bstype x, 
			bstype y, bstype* members);
#endif

		void registerAffector(const String& name, AffectorFunction func);

		AffectorFunction getAffectorFunction(const String& name);

		int addAffectorInstance(const String& name, AffectorFunction func, int numArgs, 
			const BytecodeBlock& code, ScriptMachine* machine);

		int getAffectorInstanceIndex(const String& name) const;

		Affector* getAffectorInstance(int index) const;

		inline void applyAffector(UserTypeBase* object, int index, float frameTime)
		{
			mAffectorInstances[index]->execute(object, frameTime);
		}
	
	private:

		String mName;

		int mType;

		TypeManager* mTypeManager;

		ScriptMachine* mVM;
		
		// Functions
		struct FunctionEntry
		{
			String name;
			FireFunction func;
			int numArguments;
		};

		std::vector<FunctionEntry> mFunctions;

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

		// Affector Instances
		std::vector<Affector*> mAffectorInstances;
	};

}

#endif
