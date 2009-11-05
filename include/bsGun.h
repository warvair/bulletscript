#ifndef __BS_GUN_H__
#define __BS_GUN_H__

#include "bsPrerequisites.h"
#include "bsScriptStructs.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

	class _BSAPI Gun : public DeepMemoryPoolObject
	{
	protected:

		ScriptMachine* mScriptMachine;

	public:

		GunScriptRecord* mRecord;

	public:

		explicit Gun(ScriptMachine* scriptMachine);

		~Gun();

		void setDefinition(GunDefinition* def);
		
		void setX(bstype x);

		void setY(bstype y);

		void setAngle(bstype angle);

		void setMember(int member, bstype value);

		void runScript(float frameTime);

	};

}

#endif
