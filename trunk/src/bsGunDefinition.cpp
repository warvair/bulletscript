#include <iostream>
#include "bsGunDefinition.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
GunDefinition::GunDefinition(const String& name) :
	mName(name),
	m_constructCode(0),
	m_constructSize(0),
	mNumUserMembers(0),
	mMaxLocals(0),
	mInitialState(-1)
{
}
// --------------------------------------------------------------------------------
GunDefinition::~GunDefinition()
{
	delete[] m_constructCode;
}
// --------------------------------------------------------------------------------
const String& GunDefinition::getName() const
{
	return mName;
}
// --------------------------------------------------------------------------------
void GunDefinition::setMaxLocalVariables(int count)
{
	mMaxLocals = count;
}
// --------------------------------------------------------------------------------
int GunDefinition::getMaxLocalVariables() const
{
	return mMaxLocals;
}
// --------------------------------------------------------------------------------
void GunDefinition::addMemberVariable(const String& name, bool readonly, bstype value)
{
	MemberVariable var;
	var.name = name;
	var.readonly = readonly;
	var.value = value;

	mVariables.push_back(var);
}
// --------------------------------------------------------------------------------
GunDefinition::MemberVariable& GunDefinition::getMemberVariable(int index)
{
	return mVariables[index];
}
// --------------------------------------------------------------------------------
int GunDefinition::getMemberVariableIndex(const String& name) const
{
	for (int i = 0; i < getNumMemberVariables(); ++i)
	{
		if (mVariables[i].name == name)
			return i;
	}

	return -1;
}
// --------------------------------------------------------------------------------
int GunDefinition::getNumMemberVariables() const
{
	return (int) mVariables.size();
}
// --------------------------------------------------------------------------------
void GunDefinition::setNumUserMembers(int count)
{
	mNumUserMembers = count;
}
// --------------------------------------------------------------------------------
int GunDefinition::getNumUserMembers() const
{
	return mNumUserMembers;
}
// --------------------------------------------------------------------------------
GunDefinition::Function& GunDefinition::addFunction(const String& name, ParseTreeNode* node)
{
	Function func;
	func.name = name;
	func.numArguments = 0;
	func.node = node;

	mFunctions.push_back(func);

	return mFunctions[getNumFunctions() - 1];
}
// --------------------------------------------------------------------------------
GunDefinition::Function& GunDefinition::getFunction(int index)
{
	return mFunctions[index];
}
// --------------------------------------------------------------------------------
int GunDefinition::getFunctionIndex(const String& name) const
{
	for (int i = 0; i < getNumFunctions(); ++i)
	{
		if (mFunctions[i].name == name)
			return i;
	}

	return -1;
}
// --------------------------------------------------------------------------------
int GunDefinition::getNumFunctions() const
{
	return (int) mFunctions.size();
}
// --------------------------------------------------------------------------------
GunDefinition::State& GunDefinition::addState(const String& name)
{
	State state;
	state.name = name;

	mStates.push_back(state);

	return mStates[getNumStates() - 1];
}
// --------------------------------------------------------------------------------
GunDefinition::State& GunDefinition::getState(int index)
{
	return mStates[index];
}
// --------------------------------------------------------------------------------
int GunDefinition::getStateIndex(const String& name) const
{
	for (int i = 0; i < getNumStates(); ++i)
	{
		if (mStates[i].name == name)
			return i;
	}

	return -1;
}
// --------------------------------------------------------------------------------
int GunDefinition::getNumStates() const
{
	return (int) mStates.size();
}
// --------------------------------------------------------------------------------
void GunDefinition::setInitialState(int state)
{
	mInitialState = state;
}
// --------------------------------------------------------------------------------
void GunDefinition::appendConstructionCode(const BytecodeBlock& code)
{
	m_constructor.insert(m_constructor.end(), code.begin(), code.end());
}
// --------------------------------------------------------------------------------
void GunDefinition::finaliseConstructor()
{
	m_constructSize = m_constructor.size();
	if (m_constructSize > 0)
	{
		m_constructCode = new uint32[m_constructSize];
		for (size_t i = 0; i < m_constructSize; ++i)
			m_constructCode[i] = m_constructor[i];
	}
}
// --------------------------------------------------------------------------------
GunScriptRecord* GunDefinition::createGunScriptRecord(ScriptMachine* sm)
{
	GunScriptRecord* record = new GunScriptRecord(mMaxLocals);

	// Allocate space for member vars, and set where possible
	int numMembers = getNumMemberVariables();
	if (numMembers > 0)
	{
		record->members = new bstype[numMembers];
		for (int i = 0; i < numMembers; ++i)
			record->members[i] = mVariables[i].value;
	}

	// Run construction code, if there is any
	if (m_constructSize > 0)
	{
		sm->interpretCode(m_constructCode, m_constructSize, record->scriptState,
			&record->curState, 0, 0, 0, record->members, 0, false);
		record->scriptState.stackHead = 0;
		record->scriptState.curInstruction = 0;
	}

	record->curState = mInitialState;

	return record;
}
// --------------------------------------------------------------------------------

}