#include <iostream>
#include "bsGunDefinitions.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
GunDefinition::GunDefinition(const String& name, int type) :
	mName(name),
	mType(type),
	m_constructCode(0),
	m_constructSize(0),
	mNumUserMembers(0)
{
}
// --------------------------------------------------------------------------------
GunDefinition::~GunDefinition()
{
	delete[] m_constructCode;
	
	std::vector<State>::iterator it = mStates.begin();
	while (it != mStates.end())
	{
		delete (*it).record;
		++it;
	}
}
// --------------------------------------------------------------------------------
const String& GunDefinition::getName() const
{
	return mName;
}
// --------------------------------------------------------------------------------
int GunDefinition::getType() const
{
	return mType;
}
// --------------------------------------------------------------------------------
void GunDefinition::addMemberVariable(const String& name, bool readonly)
{
	MemberVariable var;
	var.name = name;
	var.readonly = readonly;
	var.value = 0.0f;

	mVariables.push_back(var);
}
// --------------------------------------------------------------------------------
void GunDefinition::addMemberVariable(const String& name, bool readonly, float value)
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
bool GunDefinition::memberVariableExists(const String& name) const
{
	std::vector<MemberVariable>::const_iterator it = mVariables.begin();
	while (it != mVariables.end())
	{
		if ((*it).name == name)
			return true;

		++it;
	}

	return false;
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
void GunDefinition::addState(const State& state)
{
	mStates.push_back(state);
}
// --------------------------------------------------------------------------------
GunDefinition::State& GunDefinition::getState(int index)
{
	return mStates[index];
}
// --------------------------------------------------------------------------------
bool GunDefinition::stateExists(const String& name) const
{
	std::vector<State>::const_iterator it = mStates.begin();
	while (it != mStates.end())
	{
		if ((*it).name == name)
			return true;

		++it;
	}

	return false;
}
// --------------------------------------------------------------------------------
int GunDefinition::getNumStates() const
{
	return (int) mStates.size();
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
GunScriptRecord GunDefinition::createGunScriptRecord(ScriptMachine* sm) const
{
	GunScriptRecord record;

	// Allocate space for member vars, and set where possible
	for (int i = 0; i < getNumMemberVariables(); ++i)
		record.members.push_back(mVariables[i].value);

	// Run construction code, if there is any
	if (m_constructSize > 0)
	{
		sm->interpretCode(m_constructCode, m_constructSize, record, false);
		record.scriptState.stackHead = 0;
		record.scriptState.curInstruction = 0;
	}

	// Count maximum local vars and allocate space for them
	std::vector<State>::const_iterator it = mStates.begin();
	int maxVars = -1, maxState = -1, curState = 0;
	while (it != mStates.end())
	{
		const State& curSt = *it;

		int curVars = (int) curSt.record->variables.size();
		if (curVars > maxVars)
		{
			maxState = curState;
			maxVars = curVars;
		}

		GunScriptRecord::State st;
		st.name = curSt.name;
		st.record = curSt.record;

		record.states.push_back(st);

		++curState;
		++it;
	}

	for (int i = 0; i < maxVars; ++i)
		record.scriptState.locals.push_back(0.0f);

	return record;
}
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
BulletGunDefinition::BulletGunDefinition(const String& name) :
	GunDefinition(name, GT_Bullet)
{
}
// --------------------------------------------------------------------------------
void BulletGunDefinition::addBulletAffector(int index)
{
	mAffectors.push_back(index);
}
// --------------------------------------------------------------------------------
int BulletGunDefinition::getNumBulletAffectors() const
{
	return (int) mAffectors.size();
}
// --------------------------------------------------------------------------------
int BulletGunDefinition::getFirstAffector() const
{
	mAffectorIterator = mAffectors.begin();
	if (mAffectorIterator == mAffectors.end())
		return -1;
	else
		return *mAffectorIterator;
}
// --------------------------------------------------------------------------------
int BulletGunDefinition::getNextAffector() const
{
	++mAffectorIterator;
	if (mAffectorIterator == mAffectors.end())
		return -1;
	else
		return *mAffectorIterator;
}
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
AreaGunDefinition::AreaGunDefinition(const String& name) :
	GunDefinition(name, GT_Area),
	mNumPoints(0),
	mOrientation(0.0f),
	mOriginType(AO_Base)
{
}
// --------------------------------------------------------------------------------
void AreaGunDefinition::setNumPoints(int count)
{
	mNumPoints = count;
}
// --------------------------------------------------------------------------------
int AreaGunDefinition::getNumPoints() const
{
	return mNumPoints;
}
// --------------------------------------------------------------------------------
void AreaGunDefinition::setOrientation(float orientation)
{
	mOrientation = orientation;
}
// --------------------------------------------------------------------------------
float AreaGunDefinition::getOrientation() const
{
	return mOrientation;
}
// --------------------------------------------------------------------------------
void AreaGunDefinition::setOriginType(int type)
{
	mOriginType = type;
}
// --------------------------------------------------------------------------------
int AreaGunDefinition::getOriginType() const
{
	return mOriginType;
}
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
ArcGunDefinition::ArcGunDefinition(const String& name) :
	GunDefinition(name, GT_Arc),
	mOriginType(AO_Base)
{
}
// --------------------------------------------------------------------------------
void ArcGunDefinition::setOriginType(int type)
{
	mOriginType = type;
}
// --------------------------------------------------------------------------------
int ArcGunDefinition::getOriginType() const
{
	return mOriginType;
}
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

}