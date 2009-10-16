#include <assert.h>
#include <iostream>
#include <cmath>
#include "bsGun.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
Gun::Gun(ScriptMachine* sm) :
	mScriptMachine(sm)
{
}
// --------------------------------------------------------------------------------
void Gun::setMemberVariable(int index, float value)
{
	mRecord.members[index] = value;
	// Callback for affector arguments?
	// ...
}
// --------------------------------------------------------------------------------
void Gun::runScript(float frameTime)
{
	mScriptMachine->processGunState(mRecord);

	if (mRecord.scriptState.suspendTime > 0.0f)
			mRecord.scriptState.suspendTime -= frameTime;
}
// --------------------------------------------------------------------------------
void Gun::setState(const String& state)
{
	for(size_t i = 0; i < mRecord.states.size(); ++i)
	{
		if (mRecord.states[i].name == state)
		{
			mRecord.curState = (int) i;
			mRecord.scriptState.curInstruction = 0;
			mRecord.scriptState.loopDepth = 0;
			mRecord.scriptState.stackHead = 0;
			return;
		}
	}

	assert(false && "Gun::setState state not found");
}
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
GunController::GunController(ScriptMachine *scriptMachine) :
	mGun(0),
	mScriptMachine(scriptMachine)
{
}
// --------------------------------------------------------------------------------
bool GunController::setDefinition(const String& def)
{
	assert(mGun && "GunController::setDefinition mGun is null");

	const BS_NMSP::GunDefinition* gunDef = mScriptMachine->getGunDefinition(def);
	if (!gunDef)
		return false;

	mGun->setDefinition(gunDef, this);
	return true;
}
// --------------------------------------------------------------------------------
void GunController::setMemberVariable(int index, float value)
{
	assert(mGun && "GunController::setMemberVariable mGun is null");
	mGun->setMemberVariable(index, value);
}
// --------------------------------------------------------------------------------
void GunController::runScript(float frameTime)
{
	assert(mGun && "GunController::runScript mGun is null");
	mGun->runScript(frameTime);
}
// --------------------------------------------------------------------------------
void GunController::update(float frameTime, float x, float y, float angle) 
{
	if (mGun)
		mGun->update(frameTime, x, y, angle);
}
// --------------------------------------------------------------------------------

}
