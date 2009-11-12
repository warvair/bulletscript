#include "bsEmitterDefinition.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
EmitterDefinition::EmitterDefinition(const String& name) :
	mName(name),
	m_constructCode(0),
	m_constructSize(0),
	mNumUserMembers(0),
	mMaxLocals(0),
	mInitialState(-1)
{
}
// --------------------------------------------------------------------------------
EmitterDefinition::~EmitterDefinition()
{
	delete[] m_constructCode;
}
// --------------------------------------------------------------------------------
const String& EmitterDefinition::getName() const
{
	return mName;
}
// --------------------------------------------------------------------------------
void EmitterDefinition::setMaxLocalVariables(int count)
{
	mMaxLocals = count;
}
// --------------------------------------------------------------------------------
int EmitterDefinition::getMaxLocalVariables() const
{
	return mMaxLocals;
}
// --------------------------------------------------------------------------------
void EmitterDefinition::addMemberVariable(const String& name, bool readonly, bstype value)
{
	MemberVariable var;
	var.name = name;
	var.readonly = readonly;
	var.value = value;

	mMemberVariables.push_back(var);
}
// --------------------------------------------------------------------------------
EmitterDefinition::MemberVariable& EmitterDefinition::getMemberVariable(int index)
{
	return mMemberVariables[index];
}
// --------------------------------------------------------------------------------
int EmitterDefinition::getMemberVariableIndex(const String& name) const
{
	for (int i = 0; i < getNumMemberVariables(); ++i)
	{
		if (mMemberVariables[i].name == name)
			return i;
	}

	return -1;
}
// --------------------------------------------------------------------------------
int EmitterDefinition::getNumMemberVariables() const
{
	return (int) mMemberVariables.size();
}
// --------------------------------------------------------------------------------
void EmitterDefinition::setNumUserMembers(int count)
{
	mNumUserMembers = count;
}
// --------------------------------------------------------------------------------
int EmitterDefinition::getNumUserMembers() const
{
	return mNumUserMembers;
}
// --------------------------------------------------------------------------------
EmitterDefinition::Function& EmitterDefinition::addFunction(const String& name, ParseTreeNode* node)
{
	Function func;
	func.name = name;
	func.numArguments = 0;
	func.node = node;

	mFunctions.push_back(func);

	return mFunctions[getNumFunctions() - 1];
}
// --------------------------------------------------------------------------------
EmitterDefinition::Function& EmitterDefinition::getFunction(int index)
{
	return mFunctions[index];
}
// --------------------------------------------------------------------------------
int EmitterDefinition::getFunctionIndex(const String& name) const
{
	for (int i = 0; i < getNumFunctions(); ++i)
	{
		if (mFunctions[i].name == name)
			return i;
	}

	return -1;
}
// --------------------------------------------------------------------------------
int EmitterDefinition::getNumFunctions() const
{
	return (int) mFunctions.size();
}
// --------------------------------------------------------------------------------
EmitterDefinition::State& EmitterDefinition::addState(const String& name)
{
	State state;
	state.name = name;

	mStates.push_back(state);

	return mStates[getNumStates() - 1];
}
// --------------------------------------------------------------------------------
EmitterDefinition::State& EmitterDefinition::getState(int index)
{
	return mStates[index];
}
// --------------------------------------------------------------------------------
int EmitterDefinition::getStateIndex(const String& name) const
{
	for (int i = 0; i < getNumStates(); ++i)
	{
		if (mStates[i].name == name)
			return i;
	}

	return -1;
}
// --------------------------------------------------------------------------------
int EmitterDefinition::getNumStates() const
{
	return (int) mStates.size();
}
// --------------------------------------------------------------------------------
void EmitterDefinition::setInitialState(int state)
{
	mInitialState = state;
}
// --------------------------------------------------------------------------------
void EmitterDefinition::appendConstructionCode(const BytecodeBlock& code)
{
	m_constructor.insert(m_constructor.end(), code.begin(), code.end());
}
// --------------------------------------------------------------------------------
void EmitterDefinition::finaliseConstructor()
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
ScriptRecord* EmitterDefinition::createScriptRecord(ScriptMachine* sm)
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
#ifdef BS_Z_DIMENSION
		sm->interpretCode(m_constructCode, m_constructSize, record->scriptState,
			&record->curState, 0, bsvalue0, bsvalue0, bsvalue0, record->members, false);
#else
		sm->interpretCode(m_constructCode, m_constructSize, record->scriptState,
			&record->curState, 0, bsvalue0, bsvalue0, record->members, false);
#endif

		record->scriptState.stackHead = 0;
		record->scriptState.curInstruction = 0;
	}

	record->curState = mInitialState;

	return record;
}
// --------------------------------------------------------------------------------

}