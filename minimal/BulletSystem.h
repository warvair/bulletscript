#ifndef __BULLETSYSTEM_H__
#define __BULLETSYSTEM_H__

#include <vector>
#include "bsBulletScript.h"

struct Bullet
{
	bs::bstype x, y;
	bs::bstype vx, vy;
	bs::bstype speed;

	// Internal variables, do not modify in affector function!
	int __index;
	float __time;

	// For bulletscript
	bs::FireTypeControl* __ft;

	bool __active;
	char padding[15]; // pad to 48 bytes

	Bullet() : __active(false) {}
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

	static bs::Machine<Bullet>* mMachine;

	static const int BATTERY_SIZE = 2048;

	static std::vector<Bullet> mBullets;
	static std::vector<unsigned int> mFreeList[2];
	static int mStoreIndex;
	static int mUseIndex;

	static std::vector<Bullet> mSpawnedBullets;

	static int mCurBullets, mSpawned, mKilled;

	static unsigned int getFreeBulletSlot();

	static void killBullet(Bullet* b);

public:

	static void initialise(bs::Machine<Bullet>* machine);

	static void update(float frameTime);

	static void getStats(int& active, int& spawned, int& killed);

	// Scripting
	static Bullet* emitAngle(bs::bstype x, bs::bstype y, const bs::bstype* args);

	static void killBullet(void* object);

	static void setAngle(void* object, bs::bstype value);

	static bs::bstype getAngle(void* object);

};

#endif