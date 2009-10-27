#ifndef __BS_GUNDEFINITION_H__
#define __BS_GUNDEFINITION_H__

#include <vector>
#include "bsPrerequisites.h"
#include "bsScriptStructs.h"
#include "bsScriptVariables.h"
#include "bsBytecode.h"

namespace BS_NMSP
{

	class ScriptMachine;

	class ParseTreeNode;

	class _BSAPI GunDefinition
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

		explicit GunDefinition(const String& name);

		virtual ~GunDefinition();

		const String& getName() const;

		// Local variables
		void setMaxLocalVariables(int count);

		int getMaxLocalVariables() const;

		// Member variables
		void addMemberVariable(const String& name, bool readonly, bstype value = 0);

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

		// Utilities, etc
		void appendConstructionCode(const BytecodeBlock& code);

		void finaliseConstructor();

		void print(std::ostream& stream);

		// Core
		GunScriptRecord* createGunScriptRecord(ScriptMachine* sm);

	private:

		BytecodeBlock m_constructor;

		uint32* m_constructCode;

		size_t m_constructSize;
		
		std::vector<MemberVariable> mVariables;

		int mNumUserMembers;

		int mMaxLocals;

		int mInitialState;

		std::vector<Function> mFunctions;

		std::vector<State> mStates;

	private:

		String mName;
	};

}

#endif
