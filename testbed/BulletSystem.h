#ifndef __BULLETSYSTEM_H__
#define __BULLETSYSTEM_H__

#include "bsBulletScript.h"
#include "RendererGL.h"

struct Area;

struct Bullet
{
	BS::bstype x, y;
	BS::bstype vx, vy;
	BS::bstype speed;
	BS::bstype fade;

	// Internal variables, do not modify in affector function!
	int __index;
	float __time;

	// For bulletscript
	BS::FireTypeScriptRecord* __ft;

	bool __active;
	char padding[11]; // pad to 48 bytes

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

	static BS::Machine<Bullet, Area>* mMachine;

	static const int BATTERY_SIZE = 2048;

	static std::vector<Bullet> mBullets;
	static std::vector<unsigned int> mFreeList[2];
	static int mStoreIndex;
	static int mUseIndex;

	static std::vector<Bullet> mSpawnedBullets;

	static unsigned int getFreeBulletSlot();

	static void killBullet(Bullet* b);

public:

	static void initialise(BS::Machine<Bullet, Area>* machine);

	static int update(float frameTime);

	static void render(RendererGL* renderer);

	static Bullet* getBullet(int index);

	static int getNumBullets();

	// Scripting
	static Bullet* emitAngle(BS::bstype x, BS::bstype y, const BS::bstype* args);

	static void killBullet(void* object);

	static void setAngle(void* object, BS::bstype value);

	static BS::bstype getAngle(void* object);

	static void setFade(void* object, BS::bstype value);

	static BS::bstype getFade(void* object);

};

#endif