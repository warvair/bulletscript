#include "bsAffector.h"

namespace BS_NMSP
{

// --------------------------------------------------------------------------------
Affector::Affector(AffectorFunction func, int numArgs, bool volatileArgs) : 
	mFunction(func),
	mbRecalculate(true),
	mbVolatileArguments(false)
{
}
// --------------------------------------------------------------------------------
void Affector::recalculateArguments(GunScriptRecord* record)
{
}
// --------------------------------------------------------------------------------
void Affector::execute(void* object, float frameTime, GunScriptRecord* record)
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
