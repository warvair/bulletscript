#ifndef __BS_BULLETGUN_H__
#define __BS_BULLETGUN_H__

#include "bsGun.h"
#include "bsBulletMachine.h"

namespace BS_NMSP
{

	class _BSAPI BulletGunBase : public Gun
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

		// The user can pass in an object to access when a bullet is emitted, for
		// finer control over bullet emission, if they wish.
		void* mUserObject;

	public:

		BulletGunBase(ScriptMachine *sm, void* userObject = 0) :
			Gun(sm),
			mUserObject(userObject)
		{
		}

		void* getUserObject()
		{
			return mUserObject;
		}

	};

	// BulletMachine<BulletType> must be kept here, to stop BulletGunBase from
	// needing to be templated.
	template <typename BulletType>
	class _BSAPI BulletGun : public BulletGunBase
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
	class _BSAPI BulletGunController : public GunController
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