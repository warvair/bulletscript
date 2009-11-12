#include "bsControllerDefinition.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
ControllerDefinition::ControllerDefinition(const String& name) :
	mName(name),
	m_constructCode(0),
	m_constructSize(0),
	mNumUserMembers(0),
	mMaxLocals(0),
	mInitialState(-1)
{
}
// --------------------------------------------------------------------------------
ControllerDefinition::~ControllerDefinition()
{
	delete[] m_constructCode;
}
// --------------------------------------------------------------------------------
const String& ControllerDefinition::getName() const
{
	return mName;
}
// --------------------------------------------------------------------------------
void ControllerDefinition::setMaxLocalVariables(int count)
{
	mMaxLocals = count;
}
// --------------------------------------------------------------------------------
int ControllerDefinition::getMaxLocalVariables() const
{
	return mMaxLocals;
}
// --------------------------------------------------------------------------------
void ControllerDefinition::addMemberVariable(const String& name, bool readonly, bstype value)
{
	MemberVariable var;
	var.name = name;
	var.readonly = readonly;
	var.value = value;

	mMemberVariables.push_back(var);
}
// --------------------------------------------------------------------------------
ControllerDefinition::MemberVariable& ControllerDefinition::getMemberVariable(int index)
{
	return mMemberVariables[index];
}
// --------------------------------------------------------------------------------
int ControllerDefinition::getMemberVariableIndex(const String& name) const
{
	for (int i = 0; i < getNumMemberVariables(); ++i)
	{
		if (mMemberVariables[i].name == name)
			return i;
	}

	return -1;
}
// --------------------------------------------------------------------------------
int ControllerDefinition::getNumMemberVariables() const
{
	return (int) mMemberVariables.size();
}
// --------------------------------------------------------------------------------
void ControllerDefinition::setNumUserMembers(int count)
{
	mNumUserMembers = count;
}
// --------------------------------------------------------------------------------
int ControllerDefinition::getNumUserMembers() const
{
	return mNumUserMembers;
}
// --------------------------------------------------------------------------------
ControllerDefinition::EmitterVariable& ControllerDefinition::addEmitterVariable(const String& name, 
																				const String& emitter,
																				bstype x, 
																				bstype y, 
#ifdef BS_Z_DIMENSION
																				bstype z,
#endif
																				bstype angle)
{
	EmitterVariable emit;
	emit.name = name;
	emit.emitter = emitter;
	emit.x = x;
	emit.y = y;
#ifdef BS_Z_DIMENSION
	emit.z = z;
#endif

	emit.angle = angle;

	mEmitterVariables.push_back(emit);

	return mEmitterVariables[getNumEmitterVariables() - 1];
}
// --------------------------------------------------------------------------------
ControllerDefinition::EmitterVariable& ControllerDefinition::getEmitterVariable(int index)
{
	return mEmitterVariables[index];
}
// --------------------------------------------------------------------------------
int ControllerDefinition::getEmitterVariableIndex(const String& name) const
{
	for (int i = 0; i < getNumEmitterVariables(); ++i)
	{
		if (mEmitterVariables[i].name == name)
			return i;
	}

	return -1;
}
// --------------------------------------------------------------------------------
int ControllerDefinition::getNumEmitterVariables() const
{
	return (int) mEmitterVariables.size();
}
// --------------------------------------------------------------------------------
ControllerDefinition::State& ControllerDefinition::addState(const String& name)
{
	State state;
	state.name = name;

	mStates.push_back(state);

	return mStates[getNumStates() - 1];
}
// --------------------------------------------------------------------------------
ControllerDefinition::State& ControllerDefinition::getState(int index)
{
	return mStates[index];
}
// --------------------------------------------------------------------------------
int ControllerDefinition::getStateIndex(const String& name) const
{
	for (int i = 0; i < getNumStates(); ++i)
	{
		if (mStates[i].name == name)
			return i;
	}

	return -1;
}
// --------------------------------------------------------------------------------
int ControllerDefinition::getNumStates() const
{
	return (int) mStates.size();
}
// --------------------------------------------------------------------------------
void ControllerDefinition::setInitialState(int state)
{
	mInitialState = state;
}
// --------------------------------------------------------------------------------
void ControllerDefinition::appendConstructionCode(const BytecodeBlock& code)
{
	m_constructor.insert(m_constructor.end(), code.begin(), code.end());
}
// --------------------------------------------------------------------------------
void ControllerDefinition::finaliseConstructor()
{
	m_constructSize = m_constructor.size();
	if (m_constructSize > 0)
	{
		m_constructCode = new uint32[m_constructSize];
		for (size_t i = 0; i < m_constructSize; ++i)
			m_constructCode[i] = m_constructor[i];
	}

	m_constructor.clear();
}
// --------------------------------------------------------------------------------
ScriptRecord* ControllerDefinition::createScriptRecord(ScriptMachine* sm)
{
	ScriptRecord* record = new ScriptRecord(mMaxLocals);

	// Allocate space for member vars, and set where possible
	int numMembers = getNumMemberVariables();
	if (numMembers > 0)
	{
		record->members = new bstype[numMembers];
		for (int i = 0; i < numMembers; ++i)
			record->members[i] = mMemberVariables[i].value;
	}

	// Run construction code, if there is any
	if (m_constructSize > 0)
	{
		sm->interpretCode(m_constructCode, m_constructSize, record->scriptState,
			record->members);

		record->scriptState.stackHead = 0;
		record->scriptState.curInstruction = 0;
	}

	record->curState = mInitialState;

	return record;
}
// --------------------------------------------------------------------------------

}