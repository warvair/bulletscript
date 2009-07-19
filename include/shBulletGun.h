#ifndef __SH_BULLETGUN_H__
#define __SH_BULLETGUN_H__

#include "shGun.h"
#include "shBulletMachine.h"

namespace Shmuppet
{

	class _ShmuppetAPI BulletGunBase : public Gun
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

	public:

		BulletGunBase(ScriptMachine *sm) :
			Gun(sm)
		{
		}

	};

	// BulletMachine<BulletType> must be kept here, to stop BulletGunBase from
	// needing to be templated.
	template <typename BulletType>
	class _ShmuppetAPI BulletGun : public BulletGunBase
	{
		BulletMachine<BulletType>* mBulletMachine;

	public:

		BulletGun(ScriptMachine* scriptMachine, BulletMachine<BulletType>* bulletMachine) :
			BulletGunBase(scriptMachine),
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
				Affector aff;
				aff.index = *it;

				mAffectors.push_back(aff);
				++it;
			}
		}

		// This must be done here, to stop BulletGunBase from needing to be templated.
		void updateBulletAffectors()
		{
			AffectorList::iterator it = mAffectors.begin();
			while (it != mAffectors.end())
			{
				mBulletMachine->updateInstanceArguments((*it).index, (*it).arguments, mRecord);
				++it;
			}
		}

		void update(float frameTime)
		{
			updateBulletAffectors();
		}

	};

	template <typename BulletType>
	class _ShmuppetAPI BulletGunController : public GunController
	{
	public:

		BulletGunController(ScriptMachine *scriptMachine, BulletMachine<BulletType>* bulletMachine) :
			GunController(scriptMachine)
		{
			mGun = new BulletGun<BulletType>(scriptMachine, bulletMachine);
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