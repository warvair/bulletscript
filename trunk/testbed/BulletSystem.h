#ifndef __BULLETSYSTEM_H__
#define __BULLETSYSTEM_H__

#include "bsBulletScript.h"

struct Area;
struct SoundEffect;
struct Unit;
class RendererGL;

struct Bullet
{
	bs::bstype x, y;
	bs::bstype vx, vy;
	bs::bstype speed;
	bs::bstype alpha;
	bs::bstype red, green, blue;

	// Internal variables, do not modify in affector function!
	int __index;
	float __time;

	// For bulletscript
	bs::FireTypeControl* __ft;

	bool __active;
	char padding[15]; // pad to 64 bytes

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

	static bs::Machine<Bullet, Area, SoundEffect, Unit>* mMachine;

	static const int BATTERY_SIZE = 2048;

	static std::vector<Bullet> mBullets;
	static std::vector<unsigned int> mFreeList[2];
	static int mStoreIndex;
	static int mUseIndex;

	static std::vector<Bullet> mSpawnedBullets;

	static unsigned int getFreeBulletSlot();

	static void killBullet(Bullet* b);

public:

	static void initialise(bs::Machine<Bullet, Area, SoundEffect, Unit>* machine);

	static int update(float frameTime);

	static void render(RendererGL* renderer);

	static Bullet* getBullet(int index);

	static int getNumBullets();

	// Scripting
	static Bullet* emitAngle(bs::bstype x, bs::bstype y, const bs::bstype* args);

	static void killBullet(void* object);

	static void setAngle(void* object, bs::bstype value);

	static bs::bstype getAngle(void* object);

	static void setFade(void* object, bs::bstype value);

	static bs::bstype getFade(void* object);

	static void setRed(void* object, bs::bstype value);

	static bs::bstype getRed(void* object);

	static void setGreen(void* object, bs::bstype value);

	static bs::bstype getGreen(void* object);

	static void setBlue(void* object, bs::bstype value);

	static bs::bstype getBlue(void* object);

	static void gravity(void* object, float frameTime, const bs::bstype* args);
};

#endif