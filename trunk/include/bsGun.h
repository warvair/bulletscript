#ifndef __BS_GUN_H__
#define __BS_GUN_H__

#include "bsPrerequisites.h"
#include "bsScriptStructs.h"
#include "bsScriptVariables.h"
#include "bsScriptMachine.h"

namespace BS_NMSP
{

	class Gun : public DeepMemoryPoolObject
	{
	protected:

		ScriptMachine* mScriptMachine;

		GunScriptRecord* mRecord;

	public:

		explicit Gun(ScriptMachine* scriptMachine) :
			mScriptMachine(scriptMachine),
			mRecord(0)
		{
		}

		~Gun()
		{
			delete mRecord;
		}

		void setDefinition(GunDefinition* def)
		{
			if (mRecord)
				delete mRecord;

			mRecord = def->createGunScriptRecord(mScriptMachine);
		}
		
		void setMemberVariable(int index, bstype value)
		{
			mRecord->members[index] = value;
		}

		void runScript(float frameTime)
		{
			mScriptMachine->processGunState(mRecord);
			if (mRecord->scriptState.suspendTime > 0)
				mRecord->scriptState.suspendTime -= frameTime;
		}

	};

}

#endif
