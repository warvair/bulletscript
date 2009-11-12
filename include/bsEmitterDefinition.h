#ifndef __BS_EMITTERDEFINITION_H__
#define __BS_EMITTERDEFINITION_H__

#include <vector>
#include "bsPrerequisites.h"
#include "bsCore.h"
#include "bsAffector.h"
#include "bsBytecode.h"

namespace BS_NMSP
{

	class ScriptMachine;

	class ParseTreeNode;

	class _BSAPI EmitterDefinition
	{
	public:

		struct MemberVariable
		{
			String name;
			bool readonly;
			bstype value;
		};

		struct Function
		{
			String name;
			int numArguments;
			ParseTreeNode* node;
		};

		struct State
		{
			String name;
		};

	public:

		explicit EmitterDefinition(const String& name);

		~EmitterDefinition();

		const String& getName() const;

		// Local variables
		void setMaxLocalVariables(int count);

		int getMaxLocalVariables() const;

		// Member variables
		bool addMemberVariable(const String& name, bool readonly, bstype value = 0);

		MemberVariable& getMemberVariable(int index);

		int getMemberVariableIndex(const String& name) const;

		int getNumMemberVariables() const;

		void setNumUserMembers(int count);

		int getNumUserMembers() const;

		// Functions
		Function& addFunction(const String& name, ParseTreeNode* node);

		Function& getFunction(int index);
		
		int getFunctionIndex(const String& name) const;

		int getNumFunctions() const;

		// States
		State& addState(const String& name);

		State &getState(int index);

		int getStateIndex(const String& name) const;

		int getNumStates() const;

		void setInitialState(int state);

		// Constructor for member variables
		void appendConstructionCode(const BytecodeBlock& code);

		void finaliseConstructor();

		// Core
		ScriptRecord* createScriptRecord(ScriptMachine* sm);

	private:

		String mName;

		// Constructor for setting member variables
		BytecodeBlock m_constructor;

		uint32* m_constructCode;

		size_t m_constructSize;
		
		// Member variables
		std::vector<MemberVariable> mMemberVariables;

		int mNumUserMembers;

		// General info for setting up Emitter
		int mMaxLocals;

		int mInitialState;

		// Functions, states and affectors
		std::vector<Function> mFunctions;

		std::vector<State> mStates;

	};

}

#endif
