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
	setMember(Member_X, x);
}
// --------------------------------------------------------------------------------
void Emitter::setY(bstype y)
{
	setMember(Member_Y, y);
}
// --------------------------------------------------------------------------------
void Emitter::setAngle(bstype angle)
{
	setMember(Member_Angle, angle);
}
// --------------------------------------------------------------------------------
void Emitter::setMember(int member, bstype value)
{
	mRecord->members[member] = value;
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