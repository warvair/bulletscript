#include "bsAffector.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
Affector::Affector(ScriptMachine* machine, AffectorFunction func, int numArgs, bool volatileArgs) : 
	mFunction(func),
	mbRecalculate(true),
	mbVolatileArguments(false),
	mScriptMachine(machine)
{
}
// --------------------------------------------------------------------------------
void Affector::recalculateArguments(GunScriptRecord* record)
{
//	mScriptMachine->processConstantExpression(?, ?, record);
}
// --------------------------------------------------------------------------------
void Affector::execute(UserTypeBase* object, float frameTime, GunScriptRecord* record)
{
	if (mbRecalculate)
	{
		recalculateArguments(record);

		if (!mbVolatileArguments)
			mbRecalculate = false;
	}

	mFunction(object, frameTime, mState.stack + mState.stackHead);
}
// --------------------------------------------------------------------------------

}
