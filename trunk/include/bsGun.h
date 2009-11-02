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

		float mLastX, mLastY, mLastAngle;

	public:

		explicit Gun(ScriptMachine* scriptMachine) :
			mScriptMachine(scriptMachine),
			mRecord(0),
			mLastX(0),
			mLastY(0),
			mLastAngle(0)
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
		
		void setX(bstype x)
		{
			mLastX = x - mRecord->members[Member_X];
			mRecord->members[Member_X] = x;
		}

		void setY(bstype y)
		{
			mLastY = y - mRecord->members[Member_Y];
			mRecord->members[Member_Y] = y;
		}

		void setAngle(bstype angle)
		{
			mLastAngle = angle - mRecord->members[Member_Angle];
			mRecord->members[Member_Angle] = angle;
		}

		void runScript(float frameTime)
		{
			mScriptMachine->processGunState(mRecord, this);
			if (mRecord->scriptState.suspendTime > 0)
				mRecord->scriptState.suspendTime -= frameTime;
		}

		void getLastMovement(bstype& x, bstype& y)
		{
			x = mLastX;
			y = mLastY;
		}

		void getLastRotation(bstype& angle)
		{
			angle = mLastAngle;
		}

	};

}

#endif
