#ifndef __BS_CONTROLLERDEFINITION_H__
#define __BS_CONTROLLERDEFINITION_H__

#include <vector>
#include "bsPrerequisites.h"
#include "bsCore.h"
#include "bsBytecode.h"

namespace BS_NMSP
{

	class ScriptMachine;

	class _BSAPI ControllerDefinition
	{
	public:

		struct MemberVariable
		{
			String name;
			bool readonly;
			bstype value;
		};

		struct EmitterVariable
		{
			String name;
			String emitter;
		};

		struct State
		{
			String name;
		};

	public:

		explicit ControllerDefinition(const String& name);

		~ControllerDefinition();

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

		// Emitter variables
		EmitterVariable& addEmitterVariable(const String& name, const String& emitter);

		EmitterVariable& getEmitterVariable(int index);
		
		int getEmitterVariableIndex(const String& name) const;

		int getNumEmitterVariables() const;

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

		// General info for setting up Controller
		int mMaxLocals;

		int mInitialState;

		// Emitters, events and states
		std::vector<EmitterVariable> mEmitterVariables;

		std::vector<State> mStates;
		
	};

}

#endif
