#include "shGunDefinitions.h"

namespace Shmuppet
{

// --------------------------------------------------------------------------------
GunDefinition::GunDefinition(const String& name) :
	mName(name)
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
void GunDefinition::addBulletAffector(int index)
{
	mAffectors.push_back(index);
}
// --------------------------------------------------------------------------------
int GunDefinition::getNumBulletAffectors() const
{
	return (int) mAffectors.size();
}
// --------------------------------------------------------------------------------
GunScriptRecord GunDefinition::createGunScriptRecord() const
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

}