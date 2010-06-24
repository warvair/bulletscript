#include <iostream>
#include "bsAffector.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
Affector::Affector(const String& name, ScriptMachine* machine, AffectorFunction func, 
				   int numArgs, const BytecodeBlock& code) : 
	mName(name),
	mFunction(func),
	mbRecalculate(true),
	mbRecalculateAlways(false),
	mScriptMachine(machine),
	mBytecode(0),
	mBytecodeSize(0)
{
	// Copy bytecode.
	// Todo: use memcpy?
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
void Affector::recalculateArguments(void *user)
{
	mState.curInstruction = 0;
	mState.stackHead = 0;

	mScriptMachine->interpretCode(mBytecode, mBytecodeSize, mState, user);

	if (!mbRecalculateAlways)
		mbRecalculate = false;
}
// --------------------------------------------------------------------------------
void Affector::recalculateAlways(bool always)
{
	mbRecalculateAlways = always;
}
// --------------------------------------------------------------------------------
void Affector::execute(UserTypeBase* object, void* user, float frameTime)
{
	// We need to recalculate arguments, if the argument contains either a global
	// variable (which has changed) or a function call (which is unpredictable).
	if (mbRecalculate)
		recalculateArguments(user);

	mFunction(object, frameTime, mState.stack + mState.stackHead);
}
// --------------------------------------------------------------------------------
void Affector::onChanged()
{
	mbRecalculate = true;
}
// --------------------------------------------------------------------------------

}
