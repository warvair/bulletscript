#include <iostream>
#include "bsCore.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
CodeRecord::CodeRecord() :
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
	locals(0)
{
}
// --------------------------------------------------------------------------------
ScriptRecord::ScriptRecord(int numLocals) :
	curState(0),
	members(0)
{
	scriptState.curInstruction = 0;
	scriptState.loopDepth = 0;
	scriptState.stackHead = 0;
	scriptState.suspendTime = 0;

	if (numLocals > 0)
		scriptState.locals = new bstype[numLocals];
}
// --------------------------------------------------------------------------------
ScriptRecord::~ScriptRecord()
{
	delete[] members;
	delete[] scriptState.locals;
}
// --------------------------------------------------------------------------------
}
