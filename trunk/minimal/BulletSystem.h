#ifndef __BULLETSYSTEM_H__
#define __BULLETSYSTEM_H__

#include <vector>
#include "bsBulletScript.h"

struct Bullet
{
	BS::FireTypeScriptRecord* __ft;

	BS::bstype x, y;
	BS::bstype vx, vy;
	BS::bstype speed;
	BS::bstype damage;

	int stage; // for BulletAffectors
	BS::bstype speed0; // initial speed

	// Internal variables, do not modify in affector function!
	float __time;
	bool __active;
	char padding[7]; // pad to 48 bytes

	Bullet() : __active (false) {}
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

	static std::vector<Bullet> mSpawnedBullets;

	static unsigned int getFreeBulletSlot();

public:

	static void initialise();

	static Bullet* emitAngle(BS::bstype x, BS::bstype y, const BS::bstype* args);

	static int update(float frameTime, BS::Machine<Bullet>* machine);

};

#endif
