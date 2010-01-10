#include <iostream>
#include <assert.h>
#include "bsController.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
Controller::Controller(ScriptMachine* machine) :
	mEnabled(true),
	mScriptMachine(machine),
	mEmitters(0),
	mNumEmitters(0),
	mEvents(0),
	mNumEvents(0),
	mRecord(0),
	mUserObject(0)
{
	mEventState.locals = 0;
}
// --------------------------------------------------------------------------------
void Controller::onRelease()
{
	for (int i = 0; i < mNumEmitters; ++i)
		mScriptMachine->destroyEmitter(mEmitters[i].emitter);

	mBlocks.clear();

	// Note: it would be nice if we didn't do any dealloc here.
	delete[] mEmitters;
	delete[] mEvents;
	delete[] mEventState.locals;
	delete mRecord;
}
// --------------------------------------------------------------------------------
void Controller::enable(bool enable)
{
	mEnabled = enable;

	for (int i = 0; i < mNumEmitters; ++i)
		mEmitters[i].emitter->enable(enable);
}
// --------------------------------------------------------------------------------
bool Controller::isEnabled() const
{
	return mEnabled;
}
// --------------------------------------------------------------------------------
void Controller::setDefinition(ControllerDefinition* def)
{
	delete mRecord;
	mRecord = def->createScriptRecord(mScriptMachine);

	// Create the emitters that this Controller uses.
	mNumEmitters = def->getNumEmitterVariables();
	mEmitters = new EmitterInstance[mNumEmitters];

	for (int i = 0; i < mNumEmitters; ++i)
	{
		ControllerDefinition::EmitterVariable& var = def->getEmitterVariable(i);
		
		mEmitters[i] = EmitterInstance();
		EmitterInstance& inst = mEmitters[i];

		inst.special[Member_X] = var.x;
		inst.special[Member_Y] = var.y;
#ifdef BS_Z_DIMENSION
		inst.special[Member_Z] = var.z;
#endif

		inst.special[Member_Angle] = var.angle;

#ifndef BS_Z_DIMENSION
		inst.emitter = mScriptMachine->createEmitter(var.emitter, 
			mRecord->members[Member_X] + inst.special[Member_X],
			mRecord->members[Member_Y] + inst.special[Member_Y],
			mRecord->members[Member_Angle] + inst.special[Member_Angle],
			mUserObject);
#else
		inst.emitter = mScriptMachine->createEmitter(var.emitter, 
			mRecord->members[Member_X] + inst.special[Member_X],
			mRecord->members[Member_Y] + inst.special[Member_Y],
			mRecord->members[Member_Z] + inst.special[Member_Z],
			mRecord->members[Member_Angle] + inst.special[Member_Angle],
			mUserObject);

#endif

		inst.activeControllers = 0;
	}

	// Create events
	mNumEvents = def->getNumEvents();
	if (mNumEvents > 0)
		mEvents = new Event[mNumEvents];

	for (int i = 0; i < mNumEvents; ++i)
	{
		ControllerDefinition::Event& evt = def->getEvent(i);

		mEvents[i] = Event();
		Event& ctrlEvt = mEvents[i];

		ctrlEvt.name = evt.name;
		ctrlEvt.numArguments = evt.numArguments;
		ctrlEvt.code = evt.code;
	}

	int eventLocals = def->getMaxEventLocalVariables();
	if (eventLocals > 0)
		mEventState.locals = new bstype[eventLocals];
}
// --------------------------------------------------------------------------------
void Controller::setState(int state)
{
	mRecord->curState = state;
	mRecord->scriptState.curInstruction = 0;
	mRecord->scriptState.stackHead = 0;
}
// --------------------------------------------------------------------------------
void Controller::setUserObject(void* userObject)
{
	mUserObject = userObject;

	for (int i = 0; i < mNumEmitters; ++i)
		mEmitters[i].emitter->setUserObject(userObject);
}
// --------------------------------------------------------------------------------
void* Controller::getUserObject() const
{
	return mUserObject;
}
// --------------------------------------------------------------------------------
void Controller::setX(bstype x)
{
	// When controlled by a Controller, Emitter positions are stored as offsets to
	// the Controller's position.  Hence when we change the Controller position we
	// must update the Emitters'.
	mRecord->members[Member_X] = x;
	for (int i = 0; i < mNumEmitters; ++i)
		mEmitters[i].emitter->setX(mEmitters[i].special[Member_X] + x);
}
// --------------------------------------------------------------------------------
void Controller::setY(bstype y)
{
	// When controlled by a Controller, Emitter positions are stored as offsets to
	// the Controller's position.  Hence when we change the Controller position we
	// must update the Emitters'.
	mRecord->members[Member_Y] = y;
	for (int i = 0; i < mNumEmitters; ++i)
		mEmitters[i].emitter->setY(mEmitters[i].special[Member_Y] + y);
}
// --------------------------------------------------------------------------------
#ifdef BS_Z_DIMENSION
void Controller::setZ(bstype z)
{
	// When controlled by a Controller, Emitter positions are stored as offsets to
	// the Controller's position.  Hence when we change the Controller position we
	// must update the Emitters'.
	mRecord->members[Member_Z] = z;
	for (size_t i = 0; i < mNumEmitters; ++i)
		mEmitters[i].emitter->setZ(mEmitters[i].special[Member_Z] + z);
}
#endif
// --------------------------------------------------------------------------------
void Controller::setAngle(bstype angle)
{
	// When controlled by a Controller, Emitter angle is stored as an offset to
	// the Controller's.  Hence when we change the Controller angle we must update
	// the Emitters'.
	mRecord->members[Member_Angle] = angle;
	for (int i = 0; i < mNumEmitters; ++i)
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
		return mEmitters[emitter].special[member];
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
int Controller::raiseEvent(const String& evt, const bstype* args)
{
	// Note: this isn't great, but Controllers likely won't have too many events.
	for (int i = 0; i < mNumEvents; ++i)
	{
		if (mEvents[i].name == evt)
		{
			if (_raiseEvent((int) i, args))
			{
				// Suspend the Controller's script if the event has changed the state?
				// ...
			}

			return BS_OK;
		}
	}

	return BS_BadEvent;
}
// --------------------------------------------------------------------------------
bool Controller::_raiseEvent(int index, const bstype* args)
{
	// Reset our script state for the event.
	mEventState.curInstruction = 0;
	mEventState.stackHead = 0;
	mEventState.suspendTime = 0.0f;
	
	if (args)
		memcpy(mEventState.locals, args, mEvents[index].numArguments * sizeof(bstype));

	int oldState = mRecord->curState;
	mScriptMachine->interpretCode(mEvents[index].code->byteCode, mEvents[index].code->byteCodeSize,
		mEventState, 0, this, mRecord->members[Member_X], mRecord->members[Member_Y], 
		mRecord->members[Member_Angle],	mRecord->members, false, 0);

	// We need to know if the event changed the state because if it has then we should suspend the
	// script.  Otherwise the Controller's script state will be undefined.
	return oldState != mRecord->curState;
}
// --------------------------------------------------------------------------------
void Controller::addBlock(bstype block)
{
	mBlocks.push_back(block);
}
// --------------------------------------------------------------------------------
void Controller::signal(bstype block)
{
	std::list<bstype>::iterator it = mBlocks.begin();
	while (it != mBlocks.end())
	{
		if (*it == block)
		{
			std::list<bstype>::iterator next = it; ++next;
			mBlocks.erase(it);
			it = next;
		}
		else
		{
			++it;
		}
	}
}
// --------------------------------------------------------------------------------
void Controller::resume()
{
	mRecord->scriptState.suspendTime = -1;
}
// --------------------------------------------------------------------------------
void Controller::enableEmitter(int index, bool enable)
{
	mEmitters[index].emitter->enable(enable);
}
// --------------------------------------------------------------------------------
void Controller::runScript(float frameTime)
{
	// Either run the script or update the suspend time.
	if (mRecord->scriptState.suspendTime <= 0)
	{
		if (mBlocks.empty())
			mScriptMachine->processScriptRecord(mRecord, this, 0);
	}
	else
	{
		mRecord->scriptState.suspendTime -= frameTime;
	}
}
// --------------------------------------------------------------------------------
void Controller::update(float frameTime)
{
	if (!mEnabled)
		return;

	// Update special MemberControllers.  These must be stored in the Controller, not
	// the Emitter because the Emitter's members depend on the Controller's members, as
	// they are stored as offsets.
	for (int i = 0; i < mNumEmitters; ++i)
	{
		if (mEmitters[i].emitter->isEnabled())
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
	}

	// Once that's done, do some work on the Controller itself.
	runScript(frameTime);
}
// --------------------------------------------------------------------------------

}
