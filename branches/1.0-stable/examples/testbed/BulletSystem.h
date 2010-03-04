#ifndef __BULLETSYSTEM_H__
#define __BULLETSYSTEM_H__

#include "bsBulletScript.h"

class RendererGL;

struct Bullet : public bs::UserTypeBase
{
	float x, y;
	float vx, vy;
	float angle;
	float speed;
	float alpha;
	float red, green, blue;

	// Internal variables, do not modify in affector function!
	int _index;
	float _time;
	float _texture;

	bool _active;
	char padding[7]; // pad to 64 bytes

	Bullet() : _active(false) {}
};

// This class is based off code from motorherp, posted on the SHMUP-DEV forums
// at http://www.shmup-dev.com/forum

class BulletBattery
{
	static float mSinTable[3600], mCosTable[3600];

	struct BulletSorter
	{
		bool operator ()(int a, int b)
		{
			return a > b;
		}
	};

	static const int BATTERY_SIZE = 512;

	bs::Machine* mMachine;

	std::vector<Bullet> mBullets;

	std::vector<unsigned int> mFreeList[2];

	int mStoreIndex, mUseIndex;

	std::vector<Bullet> mSpawnedBullets; // should be queue

private:

	unsigned int getFreeBulletSlot();

	void killBullet(Bullet* b);

public:

	BulletBattery(bs::Machine* machine);

	static void initialiseTables();

	static float getSine(int index);

	static float getCosine(int index);

	int update(float frameTime);

	int checkCollisions(float x0, float y0, float x1, float y1);

	void render(RendererGL* renderer);

	int getCapacity() const;

	// Scripting
	bs::UserTypeBase* emitAngle(float x, float y, float angle, const float* args, void* user);

	bs::UserTypeBase* emitTarget(float x, float y, float angle, const float* args, void* user);

	void killBullet(bs::UserTypeBase* object);
};

// Function hooks
bs::UserTypeBase* bullet_emitAngle(float x, float y, float angle, const float* args, void* userObj);

bs::UserTypeBase* bullet_emitTarget(float x, float y, float angle, const float* args, void* userObj);

void bullet_kill(bs::UserTypeBase* object, void* userObj);

void bullet_setX(bs::UserTypeBase* object, float value);

float bullet_getX(bs::UserTypeBase* object);

void bullet_setY(bs::UserTypeBase* object, float value);

float bullet_getY(bs::UserTypeBase* object);

void bullet_setAngle(bs::UserTypeBase* object, float value);

float bullet_getAngle(bs::UserTypeBase* object);

void bullet_setSpeed(bs::UserTypeBase* object, float value);

float bullet_getSpeed(bs::UserTypeBase* object);

void bullet_setRed(bs::UserTypeBase* object, float value);

float bullet_getRed(bs::UserTypeBase* object);

void bullet_setGreen(bs::UserTypeBase* object, float value);

float bullet_getGreen(bs::UserTypeBase* object);

void bullet_setBlue(bs::UserTypeBase* object, float value);

float bullet_getBlue(bs::UserTypeBase* object);

void bullet_setAlpha(bs::UserTypeBase* object, float value);

float bullet_getAlpha(bs::UserTypeBase* object);

void bullet_gravity(bs::UserTypeBase* object, float frameTime, const float* args);

#endif