#include <assert.h>
#include "bsEmitter.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
Emitter::Emitter(ScriptMachine* machine) :
	mEnabled(true),
	mAnchorIndex(0),
	mLastAnchorIndex(0),
	mActiveControllers(0),
	mNumUserMembers(0),
	mLastX(bsvalue0),
	mLastY(bsvalue0),
#ifdef BS_Z_DIMENSION
	mLastZ(bsvalue0),
#endif
	mLastAngle(bsvalue0),
	mScriptMachine(machine),
	mRecord(0),
	mUserObject(0)
{
}
// --------------------------------------------------------------------------------
void Emitter::onRelease()
{
	mBlocks.clear();
BS_DELETE(mRecord);
	mRecord = 0;
	mAnchorIndex = 0;
	mUserObject = 0;
}
// --------------------------------------------------------------------------------
int Emitter::_getAnchorIndex() const
{
	return mAnchorIndex;
}
// --------------------------------------------------------------------------------
#ifndef BS_Z_DIMENSION
void Emitter::setDefinition(EmitterDefinition* def, bstype x, bstype y, bstype angle)
#else
void Emitter::setDefinition(EmitterDefinition* def, bstype x, bstype y, bstype z, bstype angle)
#endif
{
	BS_DELETE(mRecord);
	mRecord = def->createScriptRecord(mScriptMachine);

	setX(x);
	setY(y);
	setAngle(angle);
	mLastX = x;
	mLastY = y;
	mLastAngle = angle;

#ifdef BS_Z_DIMENSION
	setZ(z);
	mLastZ = z;
#endif

	// Cut anchor index down to 8 bits, to store in EmitTypeControl::flags
	mLastAnchorIndex++;
	if (mLastAnchorIndex > 255)
		mLastAnchorIndex = 1;
	mAnchorIndex = mLastAnchorIndex;

	mNumUserMembers = def->getNumMemberVariables() - NUM_SPECIAL_MEMBERS;
}
// --------------------------------------------------------------------------------
void Emitter::enable(bool enable)
{
	mEnabled = enable;
}
// --------------------------------------------------------------------------------
bool Emitter::isEnabled() const
{
	return mEnabled;
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
#ifndef BS_Z_DIMENSION
void Emitter::setPosition(bstype x, bstype y)
#else
void Emitter::setPosition(bstype x, bstype y, bstype z)
#endif
{
	mRecord->members[Member_X] = x;
	mRecord->members[Member_Y] = y;
#ifdef BS_Z_DIMENSION
	mRecord->members[Member_Z] = z;
#endif
}
// --------------------------------------------------------------------------------
void Emitter::setAngle(bstype angle)
{
	mRecord->members[Member_Angle] = angle;
}
// --------------------------------------------------------------------------------
void Emitter::setSpecialMember(int member, bstype value)
{
	assert (member >= 0 && member < NUM_SPECIAL_MEMBERS && "Emitter::setMember index must be >= 0");
	mRecord->members[member] = value;
}
// --------------------------------------------------------------------------------
void Emitter::setMember(int member, bstype value)
{
	assert (member >= 0 && "Emitter::setMember index must be >= 0");
	mRecord->members[member + NUM_SPECIAL_MEMBERS] = value;
	
	// Unset the controller if it's active, because directly setting a variable cancels
	// any smooth interpolation.
	mActiveControllers &= ~(1 << member);
}
// --------------------------------------------------------------------------------
void Emitter::setMember(int member, bstype value, float time)
{
	assert (member >= 0 && "Emitter::setMember index must be >= 0");
	mMemberControllers[member].time = time;
	mMemberControllers[member].speed = (value - mRecord->members[member + NUM_SPECIAL_MEMBERS]) / time;
	mActiveControllers |= (1 << member);
}
// --------------------------------------------------------------------------------
bstype Emitter::getMember(int member) const
{
	assert (member >= 0 && "Emitter::getMember index must be >= 0");
	return mRecord->members[member + NUM_SPECIAL_MEMBERS];
}
// --------------------------------------------------------------------------------
bstype Emitter::getX() const
{
	return mRecord->members[Member_X];
}
// --------------------------------------------------------------------------------
bstype Emitter::getY() const
{
	return mRecord->members[Member_Y];
}
// --------------------------------------------------------------------------------
#ifdef BS_Z_DIMENSION
bstype Emitter::getZ() const
{
	return mRecord->members[Member_Z];
}
#endif
// --------------------------------------------------------------------------------
bstype Emitter::getAngle() const
{
	return mRecord->members[Member_Angle];
}
// --------------------------------------------------------------------------------
bstype Emitter::_getDeltaX() const
{
	return mRecord->members[Member_X] - mLastX;
}
// --------------------------------------------------------------------------------
bstype Emitter::_getDeltaY() const
{
	return mRecord->members[Member_Y] - mLastY;
}
// --------------------------------------------------------------------------------
#ifdef BS_Z_DIMENSION
bstype Emitter::_getDeltaZ() const
{
	return mRecord->members[Member_Z] - mLastZ;
}
#endif
// --------------------------------------------------------------------------------
bstype Emitter::_getDeltaAngle() const
{
	return mRecord->members[Member_Angle] - mLastAngle;
}
// --------------------------------------------------------------------------------
void Emitter::_updateLastMembers()
{
	mLastX = mRecord->members[Member_X];
	mLastY = mRecord->members[Member_Y];
#ifdef BS_Z_DIMENSION
	mLastZ = mRecord->members[Member_Z];
#endif
	mLastAngle = mRecord->members[Member_Angle];
}
// --------------------------------------------------------------------------------
void Emitter::setState(int state)
{
	mRecord->curState = state;
	mRecord->scriptState.curInstruction = 0;
	mRecord->scriptState.stackHead = 0;
	mRecord->scriptState.suspendTime = 0;
}
// --------------------------------------------------------------------------------
void Emitter::setUserObject(void* userObject)
{
	mUserObject = userObject;
}
// --------------------------------------------------------------------------------
void* Emitter::getUserObject() const
{
	return mUserObject;
}
// --------------------------------------------------------------------------------
void Emitter::_runScript(float frameTime)
{
	// Either run the script or update the suspend time.
	if (mRecord->scriptState.suspendTime <= 0)
		mScriptMachine->processScriptRecord(mRecord, this, mUserObject);
	else
		mRecord->scriptState.suspendTime -= frameTime;
}
// --------------------------------------------------------------------------------
void Emitter::reset()
{
	setState(0);
}
// --------------------------------------------------------------------------------
void Emitter::addBlock(bstype block)
{
	mBlocks.push_back(block);
}
// --------------------------------------------------------------------------------
void Emitter::signal(bstype block)
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
void Emitter::resume()
{
	mRecord->scriptState.suspendTime = -1;
}
// --------------------------------------------------------------------------------
void Emitter::update(float frameTime)
{
	if (!mEnabled)
		return;

	// Update user MemberControllers.
	for (int i = 0; i < mNumUserMembers; ++i)
	{
		int mask = 1 << i;
		if (mActiveControllers & mask)
		{
			mRecord->members[i + NUM_SPECIAL_MEMBERS] += mMemberControllers[i].speed * frameTime;

			mMemberControllers[i].time -= frameTime;
			if (mMemberControllers[i].time <= 0)
				mActiveControllers &= ~mask;
		}
	}

	// Once that's done, do some work on the Emitter itself.
	_runScript(frameTime);
}
// --------------------------------------------------------------------------------

}