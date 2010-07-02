#include <iostream>
#include <assert.h>
#include <cmath>
#include "bsController.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
Controller::Controller(ScriptMachine* machine) :
	mEnabled(true),
	mScriptMachine(machine),
	mDirX(0),
	mDirY(0),
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
	BS_DELETEA(mEmitters);
	BS_DELETEA(mEvents);
	BS_DELETEA(mEventState.locals);
	BS_DELETE(mRecord);
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
#ifndef BS_Z_DIMENSION
void Controller::setDefinition(ControllerDefinition* def, bstype x, bstype y, bstype angle)
#else
void Controller::setDefinition(ControllerDefinition* def, bstype x, bstype y, bstype z, bstype angle)
#endif
{
	BS_DELETE(mRecord);
	mRecord = def->createScriptRecord(mScriptMachine);

	// Initialise to 0 temporarily while we set up Emitter members
	mRecord->members[Member_X] = mRecord->members[Member_Y] = mRecord->members[Member_Angle] = 0.0f;

	// Create the emitters that this Controller uses.
	mNumEmitters = def->getNumEmitterVariables();
	mEmitters = BS_NEWA(EmitterInstance, mNumEmitters);

	mDirX = sin(angle * DEG_TO_RAD);
	mDirY = cos(angle * DEG_TO_RAD);

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
			mRecord->members[Member_X] + var.x * mDirY - var.y * mDirX,
			mRecord->members[Member_Y] + var.x * mDirX + var.y * mDirY,
			mRecord->members[Member_Angle] + inst.special[Member_Angle],
			mUserObject);
#else
		inst.emitter = mScriptMachine->createEmitter(var.emitter, 
			mRecord->members[Member_X] + var.x * mDirY - var.y * mDirX,
			mRecord->members[Member_Y] + var.x * mDirX + var.y * mDirY,
			mRecord->members[Member_Z] + inst.special[Member_Z],
			mRecord->members[Member_Angle] + inst.special[Member_Angle],
			mUserObject);
#endif

		inst.activeControllers = 0;
	}

	// After emitter members have been created, set position
#ifndef BS_Z_DIMENSION
	setPosition(x, y);
#else
	setPosition(x, y, z);
#endif
	setAngle(angle, angle);

	// Create events
	mNumEvents = def->getNumEvents();
	if (mNumEvents > 0)
		mEvents = BS_NEWA(Event, mNumEvents);

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
		mEventState.locals = BS_NEWA(bstype, eventLocals);
}
// --------------------------------------------------------------------------------
void Controller::setState(int state)
{
	// Set state and reset script
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
	{
		mEmitters[i].emitter->setX(mRecord->members[Member_X] + 
			mEmitters[i].special[Member_X] * mDirY - mEmitters[i].special[Member_Y] * mDirX);

		mEmitters[i].emitter->setY(mRecord->members[Member_Y] + 
			mEmitters[i].special[Member_X] * mDirX + mEmitters[i].special[Member_Y] * mDirY);
	}
}
// --------------------------------------------------------------------------------
void Controller::setY(bstype y)
{
	// When controlled by a Controller, Emitter positions are stored as offsets to
	// the Controller's position.  Hence when we change the Controller position we
	// must update the Emitters'.
	mRecord->members[Member_Y] = y;

	for (int i = 0; i < mNumEmitters; ++i)
	{
		mEmitters[i].emitter->setX(mRecord->members[Member_X] + 
			mEmitters[i].special[Member_X] * mDirY - mEmitters[i].special[Member_Y] * mDirX);

		mEmitters[i].emitter->setY(mRecord->members[Member_Y] + 
			mEmitters[i].special[Member_X] * mDirX + mEmitters[i].special[Member_Y] * mDirY);
	}
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
#ifndef BS_Z_DIMENSION
void Controller::setPosition(bstype x, bstype y)
#else
void Controller::setPosition(bstype x, bstype y, bstype z)
#endif
{
	mRecord->members[Member_X] = x;
	mRecord->members[Member_Y] = y;
#ifdef BS_Z_DIMENSION
	mRecord->members[Member_Z] = z;
#endif

	for (int i = 0; i < mNumEmitters; ++i)
	{
		mEmitters[i].emitter->setX(mRecord->members[Member_X] + 
			mEmitters[i].special[Member_X] * mDirY - mEmitters[i].special[Member_Y] * mDirX);

		mEmitters[i].emitter->setY(mRecord->members[Member_Y] + 
			mEmitters[i].special[Member_X] * mDirX + mEmitters[i].special[Member_Y] * mDirY);

#ifdef BS_Z_DIMENSION
		mEmitters[i].emitter->setZ(mRecord->members[Member_Z]);
#endif
	}
}
// --------------------------------------------------------------------------------
void Controller::setAngle(bstype facing, bstype orbit)
{
	// There are two possible things to update: the angle in which the Emitters
	// now face, and their position relative to the Controller: when the Controller rotates,
	// we may want its Emitters to rotate around its origin.
	mRecord->members[Member_Angle] = facing;

	// Recaculate orientation vector
	mDirX = sin(-orbit * DEG_TO_RAD);
	mDirY = cos(-orbit * DEG_TO_RAD);

	for (int i = 0; i < mNumEmitters; ++i)
	{
		mEmitters[i].emitter->setAngle(mEmitters[i].special[Member_Angle] + facing);

		mEmitters[i].emitter->setX(mRecord->members[Member_X] + 
			mEmitters[i].special[Member_X] * mDirY - mEmitters[i].special[Member_Y] * mDirX);

		mEmitters[i].emitter->setY(mRecord->members[Member_Y] + 
			mEmitters[i].special[Member_X] * mDirX + mEmitters[i].special[Member_Y] * mDirY);
	}
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
		// If X or Y, want to calculate based on orientation
		mEmitters[emitter].special[member] = value;
		if (member <= Member_Y)
		{
			mEmitters[emitter].emitter->setX(mRecord->members[Member_X] + 
				mEmitters[emitter].special[Member_X] * mDirY - mEmitters[emitter].special[Member_Y] * mDirX);

			mEmitters[emitter].emitter->setY(mRecord->members[Member_Y] + 
				mEmitters[emitter].special[Member_X] * mDirX + mEmitters[emitter].special[Member_Y] * mDirY);
		}
		else
		{
			mEmitters[emitter].emitter->setSpecialMember(member, value + mRecord->members[member]);
		}
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
void Controller::runEmitterMember(int emitter, float frameTime)
{
	mEmitters[emitter].emitter->_runScript(frameTime);
}
// --------------------------------------------------------------------------------
int Controller::raiseEvent(const String& evt, const bstype* args)
{
	// Note: this isn't great, but Controllers likely won't have too many events.
	for (int i = 0; i < mNumEvents; ++i)
	{
		if (mEvents[i].name == evt)
		{
			_raiseEvent(i, args);
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
#ifdef BS_Z_DIMENSION
		mRecord->members[Member_Z],
#endif
		mRecord->members[Member_Angle],	mRecord->members, 0);

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
	// See if this Controller has any blocks of this value, and if it does, remove them.
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
					// If X or Y, want to update based on orientation
					if (j <= Member_Y)
					{
						mEmitters[i].emitter->setX(mRecord->members[Member_X] + 
							mEmitters[i].special[Member_X] * mDirY - mEmitters[i].special[Member_Y] * mDirX);

						mEmitters[i].emitter->setY(mRecord->members[Member_Y] + 
							mEmitters[i].special[Member_X] * mDirX + mEmitters[i].special[Member_Y] * mDirY);
					}
					else
					{
						mEmitters[i].emitter->setSpecialMember(j, mEmitters[i].special[j] + mRecord->members[j]);
					}

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
