#ifndef __BS_BULLETGUN_H__
#define __BS_BULLETGUN_H__

#include "bsGun.h"
#include "bsBulletMachine.h"

namespace BS_NMSP
{
	
	// BulletMachine<BulletType> must be kept here, to stop BulletGunBase from
	// needing to be templated.
	template <typename BulletType>
	class BulletGun : public BulletGunBase
	{
		BulletMachine<BulletType>* mBulletMachine;

	public:

		BulletGun(ScriptMachine* scriptMachine, BulletMachine<BulletType>* bulletMachine, void* userEmitter) :
			BulletGunBase(scriptMachine, userEmitter),
			mBulletMachine(bulletMachine)
		{
		}

		// Needs to be done here rather than in constructor - which would be more convenient -
		// because of ye olde virtual functions in constructors problem.
		void setDefinition(const GunDefinition* def, GunController* controller)
		{
			const BulletGunDefinition* bDef = dynamic_cast<const BulletGunDefinition*>(def);
			assert(bDef && "BulletGun::setDefinition definition is not a BulletGunDefinition");

			mRecord = def->createGunScriptRecord();
			mRecord.gun = this;
			mRecord.controller = controller;

			std::list<int>::iterator it = mRecord.affectors.begin();
			while (it != mRecord.affectors.end())
			{
				mAffectors[mNumAffectors++].index = *it;
				++it;
			}
		}

		// This must be done here, to stop BulletGunBase from needing to be templated.
		void updateBulletAffectors()
		{
			for (int i = 0; i < mNumAffectors; ++i)
				mBulletMachine->updateInstanceArguments(mAffectors[i].index, mAffectors[i].arguments, mRecord);
		}

		void update(float frameTime)
		{
			updateBulletAffectors();
		}

	};

	template <typename BulletType>
	class BulletGunController : public GunController
	{
	public:

		BulletGunController(ScriptMachine *scriptMachine, BulletMachine<BulletType>* bulletMachine,
							void* userObj = 0) :
			GunController(scriptMachine)
		{
			mGun = new BulletGun<BulletType>(scriptMachine, bulletMachine, userObj);
		}

		~BulletGunController()
		{
		}

		void setProperty(int prop, float value, float time)
		{
			// BulletGuns do not have any properties
		}
	};

}

#endif
