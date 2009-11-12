#include <assert.h>
#include "bsController.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
Controller::Controller(ScriptMachine* machine) :
	mScriptMachine(machine),
	mRecord(0)
{
}
// --------------------------------------------------------------------------------
Controller::~Controller()
{
	for (size_t i = 0; i < mEmitters.size(); ++i)
		mScriptMachine->destroyEmitter(mEmitters[i].emitter);

	delete mRecord;
}
// --------------------------------------------------------------------------------
void Controller::onRelease()
{
	for (size_t i = 0; i < mEmitters.size(); ++i)
		mScriptMachine->destroyEmitter(mEmitters[i].emitter);
	mEmitters.clear();
}
// --------------------------------------------------------------------------------
void Controller::setDefinition(ControllerDefinition* def)
{
	if (mRecord)
		delete mRecord;

	mRecord = def->createScriptRecord(mScriptMachine);

	// Create the emitters that this Controller uses.
	for (int i = 0; i < def->getNumEmitterVariables(); ++i)
	{
		ControllerDefinition::EmitterVariable& var = def->getEmitterVariable(i);
		
		EmitterInstance inst;
		inst.x = var.x;
		inst.y = var.y;
#ifdef BS_Z_DIMENSION
		inst.z = var.z;
#endif

		inst.angle = var.angle;

		inst.emitter = mScriptMachine->createEmitter(var.emitter);
		inst.emitter->setX(mRecord->members[Member_X] + inst.x);
		inst.emitter->setY(mRecord->members[Member_Y] + inst.y);
#ifdef BS_Z_DIMENSION
		inst.emitter->setZ(mRecord->members[Member_Z] + inst.z);
#endif

		inst.emitter->setAngle(mRecord->members[Member_Angle] + inst.angle);

		mEmitters.push_back(inst);
	}
}
// --------------------------------------------------------------------------------
void Controller::setX(bstype x)
{
	mRecord->members[Member_X] = x;
	for (size_t i = 0; i < mEmitters.size(); ++i)
		mEmitters[i].emitter->setX(mEmitters[i].x + x);
}
// --------------------------------------------------------------------------------
void Controller::setY(bstype y)
{
	mRecord->members[Member_Y] = y;
	for (size_t i = 0; i < mEmitters.size(); ++i)
		mEmitters[i].emitter->setY(mEmitters[i].y + y);
}
// --------------------------------------------------------------------------------
#ifdef BS_Z_DIMENSION
void Controller::setZ(bstype z)
{
	mRecord->members[Member_Z] = z;
	for (size_t i = 0; i < mEmitters.size(); ++i)
		mEmitters[i].emitter->setZ(mEmitters[i].z + z);
}
#endif
// --------------------------------------------------------------------------------
void Controller::setAngle(bstype angle)
{
	mRecord->members[Member_Angle] = angle;
	for (size_t i = 0; i < mEmitters.size(); ++i)
		mEmitters[i].emitter->setAngle(mEmitters[i].angle + angle);
}
// --------------------------------------------------------------------------------
void Controller::setMember(int member, bstype value)
{
	assert (member >= 0 && "Controller::setMember index must be >= 0");
	mRecord->members[member + NUM_SPECIAL_MEMBERS] = value;
}
// --------------------------------------------------------------------------------
void Controller::runScript(float frameTime)
{
	if (mRecord->scriptState.suspendTime <= 0)
		mScriptMachine->processScriptRecord(mRecord);
	else
		mRecord->scriptState.suspendTime -= frameTime;
}
// --------------------------------------------------------------------------------

}