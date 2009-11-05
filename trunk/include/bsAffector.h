#ifndef __BS_AFFECTOR_H__
#define __BS_AFFECTOR_H__

#include "bsPrerequisites.h"
#include "bsScriptStructs.h"

namespace BS_NMSP
{

	class ScriptMachine;

	class Affector
	{
		AffectorFunction mFunction;

		ScriptState mState;

		bool mbRecalculate;

		bool mbVolatileArguments;

		ScriptMachine* mScriptMachine;

		void recalculateArguments(GunScriptRecord* record);

	public:

		Affector(ScriptMachine* machine, AffectorFunction func, int numArgs, bool volatileArgs);

		void execute(UserTypeBase* object, float frameTime, GunScriptRecord* record);
	};

}

#endif
