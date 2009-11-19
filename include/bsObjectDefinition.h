#ifndef __BS_OBJECTDEFINITION_H__
#define __BS_OBJECTDEFINITION_H__

#include <vector>
#include "bsPrerequisites.h"
#include "bsCore.h"
#include "bsBytecode.h"

namespace BS_NMSP
{

	class _BSAPI ObjectDefinition
	{

	public:

		// If we can store 'value' contiguously, then we can use memcpy to
		// set members in ControllerDefinition::createScriptRecord and
		// EmitterDefinition::createScriptRecord
		struct MemberVariable
		{
			String name;
			bool readonly;
			bstype value;
		};

		struct State
		{
			String name;
		};

	public:

		ObjectDefinition(const String& name, const String& type);

		virtual ~ObjectDefinition();

		const String& getName() const;

		const String& getType() const;

		// Construction code
		void appendConstructionCode(const BytecodeBlock& code);

		void finaliseConstructor();

		// Local variables
		void setMaxLocalVariables(int count);

		int getMaxLocalVariables() const;

		// Member variables
		bool addMemberVariable(const String& name, bool readOnly, bstype value = bsvalue0);

		MemberVariable& getMemberVariable(int index);

		int getMemberVariableIndex(const String& name) const;

		int getNumMemberVariables() const;

		void setNumUserMembers(int count);

		int getNumUserMembers() const;

		// States
		State& addState(const String& name);

		State &getState(int index);

		int getStateIndex(const String& name) const;

		int getNumStates() const;

		void setInitialState(int state);

	private:

		String mName;

		String mType;

	protected:

		int mMaxLocals;

		// Constructor for setting member variables
		BytecodeBlock mConstructor;

		uint32* mConstructCode;

		size_t mConstructSize;

		// Member variables
		std::vector<MemberVariable> mMemberVariables;

		int mNumUserMembers;

		// States
		std::vector<State> mStates;

		int mInitialState;

	};

}

#endif