#ifndef __BULLETSYSTEM_H__
#define __BULLETSYSTEM_H__

#include "shGun.h"
#include "RendererGL.h"

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

	Bullet () : __active (false) {}

	// This must be added to the Bullet type in order to use BulletAffectors
	Shmuppet::GunBase *__gun;
};

/* This class is based off code from motorherp, posted on the SHMUP-DEV forums
	at http://www.shmup-dev.com/forum
*/

class BulletBattery
{
	struct BulletSorter
	{
		bool operator () (int a, int b)
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

	static void initialise ();

	static int emitAngle (Shmuppet::GunBase *gun, float x, float y, Shmuppet::uint32 *args);

	static int emitTarget (Shmuppet::GunBase *gun, float x, float y, Shmuppet::uint32 *args);

	static int update (float frameTime, Shmuppet::BulletMachine<Bullet>* bulletMachine);

	static void render (RendererGL *renderer);
};


// BulletAffector functions
void BulletAffector_Force (Bullet &b, float *args, float frameTime);

void BulletAffector_Home (Bullet &b, float *args, float frameTime);

void BulletAffector_DelayAccel (Bullet &b, float *args, float frameTime);

void BulletAffector_Explode (Bullet &b, float *args, float frameTime);

#endif