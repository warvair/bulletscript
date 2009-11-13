#include "bsEmitterDefinition.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
EmitterDefinition::EmitterDefinition(const String& name) :
	ObjectDefinition(name, "Emitter")
{
}
// --------------------------------------------------------------------------------
EmitterDefinition::Function& EmitterDefinition::addFunction(const String& name, ParseTreeNode* node)
{
	Function func;
	func.name = name;
	func.numArguments = 0;
	func.node = node;

	mFunctions.push_back(func);

	return mFunctions[getNumFunctions() - 1];
}
// --------------------------------------------------------------------------------
EmitterDefinition::Function& EmitterDefinition::getFunction(int index)
{
	return mFunctions[index];
}
// --------------------------------------------------------------------------------
int EmitterDefinition::getFunctionIndex(const String& name) const
{
	for (int i = 0; i < getNumFunctions(); ++i)
	{
		if (mFunctions[i].name == name)
			return i;
	}

	return -1;
}
// --------------------------------------------------------------------------------
int EmitterDefinition::getNumFunctions() const
{
	return (int) mFunctions.size();
}
// --------------------------------------------------------------------------------
ScriptRecord* EmitterDefinition::createScriptRecord(ScriptMachine* sm)
{
	ScriptRecord* record = new ScriptRecord(mMaxLocals);

	// Allocate space for member vars, and set where possible
	int numMembers = getNumMemberVariables();
	if (numMembers > 0)
	{
		record->members = new bstype[numMembers];
		for (int i = 0; i < numMembers; ++i)
			record->members[i] = mMemberVariables[i].value;
	}

	// Run construction code, if there is any
	if (mConstructSize > 0)
	{
		sm->interpretCode(mConstructCode, mConstructSize, record->scriptState,
			record->members);

		record->scriptState.stackHead = 0;
		record->scriptState.curInstruction = 0;
	}

	record->curState = mInitialState;

	return record;
}
// --------------------------------------------------------------------------------

}