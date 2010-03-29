#include <iostream>
#include "bsCore.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
CodeRecord::CodeRecord(const String& name) :
	mName(name),
	byteCode(0),
	byteCodeSize(0),
	jitFunction(0)
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

	return BS_NotFound;
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
		scriptState.locals = BS_NEWA(bstype, numLocals);
}
// --------------------------------------------------------------------------------
ScriptRecord::~ScriptRecord()
{
	BS_DELETEA(members);
	BS_DELETEA(scriptState.locals);
}
// --------------------------------------------------------------------------------
}
