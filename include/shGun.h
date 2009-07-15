#ifndef __SH_GUN_H__
#define __SH_GUN_H__

#include "shPrerequisites.h"
#include "shScriptDefinition.h"
#include "shScriptMachine.h"
#include "shScriptVariables.h"

namespace Shmuppet
{

	class _ShmuppetAPI GunBase 
	{
	public:
		
		static const int MAX_AFFECTOR_ARGS = 8;

		struct Affector
		{
			int index;
			float arguments[MAX_AFFECTOR_ARGS];
		};

		typedef std::list<Affector> AffectorList;
		AffectorList mAffectors;
	};

	template <typename BulletType>
	class _ShmuppetAPI Gun : public GunBase
	{
		ScriptMachine* mScriptMachine;

		BulletMachine<BulletType>* mBulletMachine;

		GunScriptRecord mRecord;

	public:

		Gun(ScriptMachine* scriptMachine, BulletMachine<BulletType>* bulletMachine) :
			GunBase(),
			mScriptMachine(scriptMachine),
			mBulletMachine(bulletMachine)
		{
		}

		void setDefinition(GunDefinition* def)
		{
			mRecord = def->createGunScriptRecord();

			mRecord.gun = this;

			// Create affectors
			std::list<int>::iterator it = mRecord.affectors.begin();
			while (it != mRecord.affectors.end())
			{
				Affector aff;
				aff.index = *it;

				mAffectors.push_back(aff);
				++it;
			}
		}

		void runScript(float frameTime)
		{
			mScriptMachine->processGunState(mRecord);

			if (mRecord.suspendTime > 0.0f)
					mRecord.suspendTime -= frameTime;
		}

		void setInstanceVariable(int index, float value)
		{
			assert(index >= 0 && index < NUM_INSTANCE_VARS &&
				"Gun::setInstanceVariable: out of bounds.");

			mRecord.instanceVars[index] = value;
		}

		void updateBulletAffectors()
		{
			AffectorList::iterator it = mAffectors.begin();
			while (it != mAffectors.end())
			{
				mBulletMachine->updateInstanceArguments((*it).index, (*it).arguments, mRecord);
				++it;
			}
		}

	};

}

#endif
