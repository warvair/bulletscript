#include <assert.h>
#include "bsEmitter.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
Emitter::Emitter(ScriptMachine* scriptMachine) :
	mScriptMachine(scriptMachine),
	mRecord(0)
{
}
// --------------------------------------------------------------------------------
Emitter::~Emitter()
{
	delete mRecord;
}
// --------------------------------------------------------------------------------
void Emitter::setDefinition(EmitterDefinition* def)
{
	if (mRecord)
		delete mRecord;

	mRecord = def->createScriptRecord(mScriptMachine);
}
// --------------------------------------------------------------------------------
void Emitter::setX(bstype x)
{
	mRecord->members[Member_X] = x;
}
// --------------------------------------------------------------------------------
void Emitter::setY(bstype y)
{
	mRecord->members[Member_Y] = y;
}
// --------------------------------------------------------------------------------
#ifdef BS_Z_DIMENSION
void Emitter::setZ(bstype z)
{
	mRecord->members[Member_Z] = z;
}
#endif
// --------------------------------------------------------------------------------
void Emitter::setAngle(bstype angle)
{
	mRecord->members[Member_Angle] = angle;
}
// --------------------------------------------------------------------------------
void Emitter::setMember(int member, bstype value)
{
	assert (member >= 0 && "Emitter::setMember index must be >= 0");
	mRecord->members[member + NUM_SPECIAL_MEMBERS] = value;
}
// --------------------------------------------------------------------------------
void Emitter::runScript(float frameTime)
{
	mScriptMachine->processScriptRecord(mRecord);
	if (mRecord->scriptState.suspendTime > 0)
		mRecord->scriptState.suspendTime -= frameTime;
}
// --------------------------------------------------------------------------------

}