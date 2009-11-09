#include "bsGun.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
Gun::Gun(ScriptMachine* scriptMachine) :
	mScriptMachine(scriptMachine),
	mRecord(0)
{
}
// --------------------------------------------------------------------------------
Gun::~Gun()
{
	delete mRecord;
}
// --------------------------------------------------------------------------------
void Gun::setDefinition(GunDefinition* def)
{
	if (mRecord)
		delete mRecord;

	mRecord = def->createGunScriptRecord(mScriptMachine);
}
// --------------------------------------------------------------------------------
void Gun::setX(bstype x)
{
	setMember(Member_X, x);
}
// --------------------------------------------------------------------------------
void Gun::setY(bstype y)
{
	setMember(Member_Y, y);
}
// --------------------------------------------------------------------------------
void Gun::setAngle(bstype angle)
{
	setMember(Member_Angle, angle);
}
// --------------------------------------------------------------------------------
void Gun::setMember(int member, bstype value)
{
	mRecord->members[member] = value;
}
// --------------------------------------------------------------------------------
void Gun::runScript(float frameTime)
{
	mScriptMachine->processGunState(mRecord, this);
	if (mRecord->scriptState.suspendTime > 0)
		mRecord->scriptState.suspendTime -= frameTime;
}
// --------------------------------------------------------------------------------

}