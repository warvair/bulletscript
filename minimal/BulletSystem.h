#ifndef __BULLETSYSTEM_H__
#define __BULLETSYSTEM_H__

#include "bsBulletGun.h"

struct Bullet
{
	float x, y;
	float vx, vy;
	float speed;
	float damage;

	int stage; // for BulletAffectors
	float speed0; // initial speed

	// Internal variables, do not modify in affector function!
	float __time;
	bool __active;
	char padding[7]; // pad to 48 bytes

	Bullet() : __active (false) {}

	// This must be added to the Bullet type in order to use BulletAffectors
	BS::BulletGunBase *__gun;
};

/* This class is based off code from motorherp, posted on the SHMUP-DEV forums
	at http://www.shmup-dev.com/forum
*/

class BulletBattery
{
	struct BulletSorter
	{
		bool operator ()(int a, int b)
		{
			return a > b;
		}
	};

	static const int BATTERY_SIZE = 2048;

	static std::vector<Bullet> mBullets;
	static std::vector<unsigned int> mFreeList[2];
	static int mStoreIndex;
	static int mUseIndex;

	static unsigned int getFreeBulletSlot();

public:

	static void initialise();

	static int emitAngle(BS::BulletGunBase* gun, float x, float y, const float* args);

	static int emitTarget(BS::BulletGunBase* gun, float x, float y, const float* args);

	static int update(float frameTime, BS::BulletMachine<Bullet>* bulletMachine);

};


// BulletAffector functions
void BulletAffector_Accel(Bullet& b, const float* args, float frameTime);

void BulletAffector_Force(Bullet& b, const float* args, float frameTime);

void BulletAffector_DelayAccel(Bullet& b, const float* args, float frameTime);

void BulletAffector_Explode(Bullet& b, const float* args, float frameTime);

#endif
