#include "shGunDefinitions.h"

namespace Shmuppet
{

// --------------------------------------------------------------------------------
GunDefinition::GunDefinition(const String& name, int type) :
	mName(name),
	mType(type)
{
}
// --------------------------------------------------------------------------------
GunDefinition::~GunDefinition()
{
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
GunScriptRecord BulletGunDefinition::createGunScriptRecord() const
{
	GunScriptRecord record;

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
		record.variables.push_back(0.0f);

	std::list<int>::const_iterator aIt = mAffectors.begin();
	while (aIt != mAffectors.end())
	{
		record.affectors.push_back(*aIt);
		++aIt;
	}

	return record;
}
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
AreaGunDefinition::AreaGunDefinition(const String& name) :
	GunDefinition(name, GT_Area),
	mNumPoints(0),
	mOrientation(0.0f)
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
GunScriptRecord AreaGunDefinition::createGunScriptRecord() const
{
	GunScriptRecord record;

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
		record.variables.push_back(0.0f);

	return record;
}
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
SplineGunDefinition::SplineGunDefinition(const String& name) :
	GunDefinition(name, GT_Spline)
{
}
// --------------------------------------------------------------------------------
GunScriptRecord SplineGunDefinition::createGunScriptRecord() const
{
	GunScriptRecord record;

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
		record.variables.push_back(0.0f);

	return record;
}
// --------------------------------------------------------------------------------

}