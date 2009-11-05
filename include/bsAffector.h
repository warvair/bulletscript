#ifndef __BS_AFFECTOR_H__
#define __BS_AFFECTOR_H__

#include "bsPrerequisites.h"
#include "bsScriptStructs.h"

namespace BS_NMSP
{

	class Affector
	{
		AffectorFunction mFunction;

		ScriptState mState;

		bool mbRecalculate;

		bool mbVolatileArguments;

		void recalculateArguments(GunScriptRecord* record);

	public:

		Affector(AffectorFunction func, int numArgs, bool volatileArgs);

		void execute(void* object, float frameTime, GunScriptRecord* record);
	};

}

#endif
