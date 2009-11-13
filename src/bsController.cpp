#include <iostream>
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
		inst.special[Member_X] = var.x;
		inst.special[Member_Y] = var.y;
#ifdef BS_Z_DIMENSION
		inst.special[Member_Z] = var.z;
#endif

		inst.special[Member_Angle] = var.angle;

		inst.emitter = mScriptMachine->createEmitter(var.emitter);
		inst.emitter->setX(mRecord->members[Member_X] + inst.special[Member_X]);
		inst.emitter->setY(mRecord->members[Member_Y] + inst.special[Member_Y]);
#ifdef BS_Z_DIMENSION
		inst.emitter->setZ(mRecord->members[Member_Z] + inst.special[Member_Z]);
#endif

		inst.emitter->setAngle(mRecord->members[Member_Angle] + inst.special[Member_Angle]);
		inst.activeControllers = 0;

		mEmitters.push_back(inst);
	}
}
// --------------------------------------------------------------------------------
void Controller::setX(bstype x)
{
	mRecord->members[Member_X] = x;
	for (size_t i = 0; i < mEmitters.size(); ++i)
		mEmitters[i].emitter->setX(mEmitters[i].special[Member_X] + x);
}
// --------------------------------------------------------------------------------
void Controller::setY(bstype y)
{
	mRecord->members[Member_Y] = y;
	for (size_t i = 0; i < mEmitters.size(); ++i)
		mEmitters[i].emitter->setY(mEmitters[i].special[Member_Y] + y);
}
// --------------------------------------------------------------------------------
#ifdef BS_Z_DIMENSION
void Controller::setZ(bstype z)
{
	mRecord->members[Member_Z] = z;
	for (size_t i = 0; i < mEmitters.size(); ++i)
		mEmitters[i].emitter->setZ(mEmitters[i].special[Member_Z] + z);
}
#endif
// --------------------------------------------------------------------------------
void Controller::setAngle(bstype angle)
{
	mRecord->members[Member_Angle] = angle;
	for (size_t i = 0; i < mEmitters.size(); ++i)
		mEmitters[i].emitter->setAngle(mEmitters[i].special[Member_Angle] + angle);
}
// --------------------------------------------------------------------------------
void Controller::setMember(int member, bstype value)
{
	assert (member >= 0 && "Controller::setMember index must be >= 0");
	mRecord->members[member + NUM_SPECIAL_MEMBERS] = value;
}
// --------------------------------------------------------------------------------
void Controller::setEmitterMember(int emitter, int member, bstype value)
{
	if (member < NUM_SPECIAL_MEMBERS)
	{
		mEmitters[emitter].special[member] = value;
		mEmitters[emitter].emitter->setSpecialMember(member, value + mRecord->members[member]);
	}
	else
	{
		mEmitters[emitter].emitter->setMember(member - NUM_SPECIAL_MEMBERS, value);
	}
}
// --------------------------------------------------------------------------------
void Controller::setEmitterMember(int emitter, int member, bstype value, float time)
{
	if (member < NUM_SPECIAL_MEMBERS)
	{
		mEmitters[emitter].controllers[member].time = time;
		mEmitters[emitter].controllers[member].speed = (value - mEmitters[emitter].special[member]) / time;
		mEmitters[emitter].activeControllers |= (1 << member);
	}
	else
	{
		mEmitters[emitter].emitter->setMember(member - NUM_SPECIAL_MEMBERS, value, time);
	}
}
// --------------------------------------------------------------------------------
bstype Controller::getEmitterMember(int emitter, int member) const
{
	if (member < NUM_SPECIAL_MEMBERS)
	{
		return bsvalue0;
	}
	else
	{
		return mEmitters[emitter].emitter->getMember(member - NUM_SPECIAL_MEMBERS);
	}
}
// --------------------------------------------------------------------------------
void Controller::setEmitterMemberState(int emitter, int state)
{
	mEmitters[emitter].emitter->setState(state);
}
// --------------------------------------------------------------------------------
void Controller::runScript(float frameTime)
{
	if (mRecord->scriptState.suspendTime <= 0)
		mScriptMachine->processScriptRecord(mRecord, this);
	else
		mRecord->scriptState.suspendTime -= frameTime;
}
// --------------------------------------------------------------------------------
void Controller::update(float frameTime)
{
	// Update special MemberControllers.
	for (size_t i = 0; i < mEmitters.size(); ++i)
	{
		for (int j = 0; j < NUM_SPECIAL_MEMBERS; ++j)
		{
			int mask = 1 << j;
			if (mEmitters[i].activeControllers & mask)
			{
				mEmitters[i].special[j] += mEmitters[i].controllers[j].speed * frameTime;
				mEmitters[i].emitter->setSpecialMember(j, mEmitters[i].special[j] + mRecord->members[j]);

				mEmitters[i].controllers[j].time -= frameTime;
				if (mEmitters[i].controllers[j].time <= 0)
					mEmitters[i].activeControllers &= ~mask;
			}
		}
	}

	runScript(frameTime);
}
// --------------------------------------------------------------------------------

}