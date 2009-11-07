#include "bsAffector.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
Affector::Affector(const String& name, ScriptMachine* machine, AffectorFunction func, 
				   int numArgs, bool volatileArgs, const BytecodeBlock& code) : 
	mName(name),
	mFunction(func),
	mbRecalculate(true),
	mbVolatileArguments(false),
	mScriptMachine(machine),
	mBytecode(0),
	mBytecodeSize(0)
{
	if (!code.empty())
	{
		mBytecodeSize = code.size();
		mBytecode = new uint32[mBytecodeSize];
		for (size_t i = 0; i < mBytecodeSize; ++i)
			mBytecode[i] = code[i];
	}
}
// --------------------------------------------------------------------------------
Affector::~Affector()
{
	delete[] mBytecode;
}
// --------------------------------------------------------------------------------
const String& Affector::getName() const
{
	return mName;
}
// --------------------------------------------------------------------------------
void Affector::recalculateArguments(GunScriptRecord* record)
{
	mState.curInstruction = 0;
	mState.stackHead = 0;
	mScriptMachine->interpretCode(mBytecode, mBytecodeSize, mState, 0, 0,
		record->members[Member_X], record->members[Member_Y], record->members, 0, false);

	if (!mbVolatileArguments)
		mbRecalculate = false;
}
// --------------------------------------------------------------------------------
void Affector::execute(UserTypeBase* object, float frameTime, GunScriptRecord* record)
{
	if (mbRecalculate)
		recalculateArguments(record);

	mFunction(object, frameTime, mState.stack + mState.stackHead);
}
// --------------------------------------------------------------------------------

}
