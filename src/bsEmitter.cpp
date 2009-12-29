#include <assert.h>
#include "bsEmitter.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
Emitter::Emitter(ScriptMachine* machine) :
	mEnabled(true),
	mActiveControllers(0),
	mNumUserMembers(0),
	mScriptMachine(machine),
	mRecord(0),
	mUserObject(0)
{
}
// --------------------------------------------------------------------------------
void Emitter::onRelease()
{
	delete mRecord;
}
// --------------------------------------------------------------------------------
void Emitter::setDefinition(EmitterDefinition* def)
{
	delete mRecord;
	mRecord = def->createScriptRecord(mScriptMachine);

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
void Emitter::addAnchoredObject(int anchor, UserTypeBase* object)
{
}
// --------------------------------------------------------------------------------
void Emitter::setState(int state)
{
	mRecord->curState = state;
	mRecord->scriptState.curInstruction = 0;
	mRecord->scriptState.stackHead = 0;
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
void Emitter::runScript(float frameTime)
{
	// Either run the script or update the suspend time.
	if (mRecord->scriptState.suspendTime <= 0)
		mScriptMachine->processScriptRecord(mRecord, this, mUserObject);
	else
		mRecord->scriptState.suspendTime -= frameTime;
}
// --------------------------------------------------------------------------------
void Emitter::update(float frameTime)
{
	// Update anchored objects first
	// Go through X list
	// Go through Y list
	// Go through angle list

	// Rather, we need a way to give Emitters properties.  They have x, y and angle, but we may
	// want them to have red/green/blue as well?  What could this be used for?  It means that we
	// could change a property of an emitted object externally by changing the Emitter, and thus
	// Emitters can control objects like Controllers control Emitters.

	// Need a way to tie property names to indices.  We can tie x and y easily enough because they
	// are built in, but angle will need something else because it is defined by the user.

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
	runScript(frameTime);
}
// --------------------------------------------------------------------------------

}