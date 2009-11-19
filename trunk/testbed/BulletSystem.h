#ifndef __BULLETSYSTEM_H__
#define __BULLETSYSTEM_H__

#include "bsBulletScript.h"

class RendererGL;

struct Bullet : public bs::UserTypeBase
{
	bs::bstype x, y;
	bs::bstype angle;
	bs::bstype vx, vy;
	bs::bstype speed;
	bs::bstype alpha;
	bs::bstype red, green, blue;

	// Internal variables, do not modify in affector function!
	int __index;
	float __time;

	bool __active;
	char padding[11]; // pad to 64 bytes

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

	static bs::Machine* mMachine;

	static const int BATTERY_SIZE = 2048;

	static std::vector<Bullet> mBullets;
	static std::vector<unsigned int> mFreeList[2];
	static int mStoreIndex;
	static int mUseIndex;

	static float sinTable[3600], cosTable[3600];

	static std::vector<Bullet> mSpawnedBullets;

	static unsigned int getFreeBulletSlot();

	static void killBullet(Bullet* b);

public:

	static void initialise(bs::Machine* machine);

	static int update(float frameTime, int* numBullets = 0);

	static void render(RendererGL* renderer);

	static Bullet* getBullet(int index);

	static int getNumBullets();

	// Scripting
	static bs::UserTypeBase* emitAngle(bs::bstype x, bs::bstype y, const bs::bstype* args);

	static void killBullet(bs::UserTypeBase* object);

	static void setAngle(bs::UserTypeBase* object, bs::bstype value);

	static bs::bstype getAngle(bs::UserTypeBase* object);

	static void setFade(bs::UserTypeBase* object, bs::bstype value);

	static bs::bstype getFade(bs::UserTypeBase* object);

	static void setRed(bs::UserTypeBase* object, bs::bstype value);

	static bs::bstype getRed(bs::UserTypeBase* object);

	static void setGreen(bs::UserTypeBase* object, bs::bstype value);

	static bs::bstype getGreen(bs::UserTypeBase* object);

	static void setBlue(bs::UserTypeBase* object, bs::bstype value);

	static bs::bstype getBlue(bs::UserTypeBase* object);

	static void gravity(bs::UserTypeBase* object, float frameTime, const bs::bstype* args);
};

#endif