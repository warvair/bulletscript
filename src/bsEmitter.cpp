#include <assert.h>
#include "bsEmitter.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
Emitter::Emitter(ScriptMachine* scriptMachine) :
	mEnabled(true),
	mActiveControllers(0),
	mNumUserMembers(0),
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

	mNumUserMembers = def->getNumMemberVariables() - NUM_SPECIAL_MEMBERS;
}
// --------------------------------------------------------------------------------
void Emitter::enable(bool enable)
{
	mEnabled = enable;
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
	// Unset if controller active
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
void Emitter::setState(int state)
{
	mRecord->curState = state;
	mRecord->scriptState.curInstruction = 0;
	mRecord->scriptState.stackHead = 0;
}
// --------------------------------------------------------------------------------
void Emitter::runScript(float frameTime)
{
	if (mRecord->scriptState.suspendTime <= 0)
		mScriptMachine->processScriptRecord(mRecord, this);
	else
		mRecord->scriptState.suspendTime -= frameTime;
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

	// Run script
	runScript(frameTime);
}
// --------------------------------------------------------------------------------

}