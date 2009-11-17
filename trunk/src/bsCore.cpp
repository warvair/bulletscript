#include <iostream>
#include "bsCore.h"
#include "bsScriptMachine.h"
#include "bsAlloc.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
CodeRecord::CodeRecord(const String& name) :
	mName(name),
	byteCode(0),
	byteCodeSize(0)
{
}
// --------------------------------------------------------------------------------
CodeRecord::~CodeRecord()
{
	delete[] byteCode;
}
// --------------------------------------------------------------------------------
const String& CodeRecord::getName() const
{
	return mName;
}
// --------------------------------------------------------------------------------
void CodeRecord::addVariable(const String& name)
{
	mVariables.push_back(name);
}
// --------------------------------------------------------------------------------
const String& CodeRecord::getVariable(int index) const
{
	return mVariables[index];
}
// --------------------------------------------------------------------------------
int CodeRecord::getVariableIndex(const String& name) const
{
	for (int i = 0; i < getNumVariables(); ++i)
	{
		if (mVariables[i] == name)
			return i;
	}

	return -1;
}
// --------------------------------------------------------------------------------
int CodeRecord::getNumVariables() const
{
	return (int) mVariables.size();
}
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
ScriptState::ScriptState() :
	locals(0),
	curInstruction(0),
	stackHead(0),
	suspendTime(0.0f)
{
}
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
ScriptRecord::ScriptRecord(int numLocals) :
	curState(0),
	members(0)
{
	if (numLocals > 0)
	{
//		scriptState.locals = (bstype*) SmallAllocator::alloc(numLocals * sizeof(bstype));
		scriptState.locals = new bstype[numLocals];
	}
}
// --------------------------------------------------------------------------------
ScriptRecord::~ScriptRecord()
{
	delete[] members;
//	SmallAllocator::release(scriptState.locals);
	delete[] scriptState.locals;
}
// --------------------------------------------------------------------------------
}
