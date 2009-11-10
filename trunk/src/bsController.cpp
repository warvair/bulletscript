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
	delete mRecord;

	for (size_t i = 0; i < mEmitters.size(); ++i)
		mScriptMachine->destroyEmitter(mEmitters[i].emitter);
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
		inst.angle = var.angle;

		inst.emitter = mScriptMachine->createEmitter(var.emitter);
		inst.emitter->setX(mRecord->members[Member_X] + inst.x);
		inst.emitter->setY(mRecord->members[Member_Y] + inst.y);
		inst.emitter->setAngle(mRecord->members[Member_Angle] + inst.angle);

		mEmitters.push_back(inst);
	}
}
// --------------------------------------------------------------------------------
void Controller::setX(bstype x)
{
	setMember(Member_X, x);
	for (size_t i = 0; i < mEmitters.size(); ++i)
		mEmitters[i].emitter->setX(mEmitters[i].x + x);
}
// --------------------------------------------------------------------------------
void Controller::setY(bstype y)
{
	setMember(Member_Y, y);
	for (size_t i = 0; i < mEmitters.size(); ++i)
		mEmitters[i].emitter->setY(mEmitters[i].y + y);
}
// --------------------------------------------------------------------------------
void Controller::setAngle(bstype angle)
{
	setMember(Member_Angle, angle);
	for (size_t i = 0; i < mEmitters.size(); ++i)
		mEmitters[i].emitter->setAngle(mEmitters[i].angle + angle);
}
// --------------------------------------------------------------------------------
void Controller::setMember(int member, bstype value)
{
	mRecord->members[member] = value;
}
// --------------------------------------------------------------------------------
void Controller::runScript(float frameTime)
{
	mScriptMachine->processScriptRecord(mRecord);
	if (mRecord->scriptState.suspendTime > 0)
		mRecord->scriptState.suspendTime -= frameTime;
}
// --------------------------------------------------------------------------------

}