#include <assert.h>
#include <iostream>
#include <cmath>
#include "shGun.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
Gun::Gun(ScriptMachine* sm) :
	mScriptMachine(sm)
{
}
// --------------------------------------------------------------------------------
void Gun::setInstanceVariable(int index, float value)
{
	assert(index >= 0 && index < NUM_INSTANCE_VARS &&
		"Gun::setInstanceVariable: out of bounds.");

	mRecord.instanceVars[index] = value;
}
// --------------------------------------------------------------------------------
void Gun::runScript(float frameTime)
{
	mScriptMachine->processGunState(mRecord);

	if (mRecord.suspendTime > 0.0f)
			mRecord.suspendTime -= frameTime;
}
// --------------------------------------------------------------------------------
void Gun::setState(const String& state)
{
	for(size_t i = 0; i < mRecord.states.size(); ++i)
	{
		if (mRecord.states[i].name == state)
		{
			mRecord.curState = (int) i;
			mRecord.curInstruction = 0;
			mRecord.repeats.clear();
			mRecord.stackHead = 0;
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
void GunController::setInstanceVariable(int index, float value)
{
	assert(mGun && "GunController::setInstanceVariable mGun is null");
	mGun->setInstanceVariable(index, value);
}
// --------------------------------------------------------------------------------
void GunController::runScript(float frameTime)
{
	assert(mGun && "GunController::runScript mGun is null");
	mGun->runScript(frameTime);
}
// --------------------------------------------------------------------------------
void GunController::update(float frameTime) 
{
	if (mGun)
		mGun->update(frameTime);
}
// --------------------------------------------------------------------------------

}