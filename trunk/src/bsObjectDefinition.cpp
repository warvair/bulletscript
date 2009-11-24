#include "bsObjectDefinition.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
ObjectDefinition::ObjectDefinition(const String& name, const String& type) :
	mName(name),
	mType(type),
	mMaxLocals(0),
	mConstructCode(0),
	mConstructSize(0),
	mNumUserMembers(0),
	mInitialState(-1)
{
}
// --------------------------------------------------------------------------------
ObjectDefinition::~ObjectDefinition()
{
	delete[] mConstructCode;
}
// --------------------------------------------------------------------------------
const String& ObjectDefinition::getName() const
{
	return mName;
}
// --------------------------------------------------------------------------------
const String& ObjectDefinition::getType() const
{
	return mType;
}
// --------------------------------------------------------------------------------
void ObjectDefinition::setMaxLocalVariables(int count)
{
	mMaxLocals = count;
}
// --------------------------------------------------------------------------------
int ObjectDefinition::getMaxLocalVariables() const
{
	return mMaxLocals;
}
// --------------------------------------------------------------------------------
bool ObjectDefinition::addMemberVariable(const String& name, bool readOnly, bstype value)
{
	int numVars = getNumMemberVariables();
	if (numVars >= (BS_MAX_USER_EMITTER_MEMBERS + NUM_SPECIAL_MEMBERS))
		return false;

	MemberVariable var;
	var.name = name;
	var.readonly = readOnly;
	var.value = value;

	mMemberVariables.push_back(var);
	return true;
}
// --------------------------------------------------------------------------------
ObjectDefinition::MemberVariable& ObjectDefinition::getMemberVariable(int index)
{
	return mMemberVariables[index];
}
// --------------------------------------------------------------------------------
int ObjectDefinition::getMemberVariableIndex(const String& name) const
{
	for (int i = 0; i < getNumMemberVariables(); ++i)
	{
		if (mMemberVariables[i].name == name)
			return i;
	}

	return -1;
}
// --------------------------------------------------------------------------------
int ObjectDefinition::getNumMemberVariables() const
{
	return (int) mMemberVariables.size();
}
// --------------------------------------------------------------------------------
void ObjectDefinition::setNumUserMembers(int count)
{
	mNumUserMembers = count;
}
// --------------------------------------------------------------------------------
int ObjectDefinition::getNumUserMembers() const
{
	return mNumUserMembers;
}
// --------------------------------------------------------------------------------
ObjectDefinition::State& ObjectDefinition::addState(const String& name)
{
	State state;
	state.name = name;

	int stateIndex = getNumStates();
	mStates.push_back(state);

	return mStates[stateIndex];
}
// --------------------------------------------------------------------------------
ObjectDefinition::State& ObjectDefinition::getState(int index)
{
	return mStates[index];
}
// --------------------------------------------------------------------------------
int ObjectDefinition::getStateIndex(const String& name) const
{
	for (int i = 0; i < getNumStates(); ++i)
	{
		if (mStates[i].name == name)
			return i;
	}

	return -1;
}
// --------------------------------------------------------------------------------
int ObjectDefinition::getNumStates() const
{
	return (int) mStates.size();
}
// --------------------------------------------------------------------------------
void ObjectDefinition::setInitialState(int state)
{
	mInitialState = state;
}
// --------------------------------------------------------------------------------
void ObjectDefinition::appendConstructionCode(const BytecodeBlock& code)
{
	mConstructor.insert(mConstructor.end(), code.begin(), code.end());
}
// --------------------------------------------------------------------------------
void ObjectDefinition::finaliseConstructor()
{
	mConstructSize = mConstructor.size();
	if (mConstructSize > 0)
	{
		mConstructCode = new uint32[mConstructSize];
		for (size_t i = 0; i < mConstructSize; ++i)
			mConstructCode[i] = mConstructor[i];
	}

	mConstructor.clear();
}
// --------------------------------------------------------------------------------



}