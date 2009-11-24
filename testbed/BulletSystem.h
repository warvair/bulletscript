#ifndef __BULLETSYSTEM_H__
#define __BULLETSYSTEM_H__

#include "bsBulletScript.h"

class RendererGL;

struct Bullet : public bs::UserTypeBase
{
	float x, y;
	float angle;
	float vx, vy;
	float speed;
	float alpha;
	float red, green, blue;

	// Internal variables, do not modify in affector function!
	int __index;
	float __time;

	bool __active;
	char padding[11]; // pad to 64 bytes

	Bullet() : __active(false) {}
};

// This class is based off code from motorherp, posted on the SHMUP-DEV forums
// at http://www.shmup-dev.com/forum

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

	bs::Machine* mMachine;

	std::vector<Bullet> mBullets;

	std::vector<unsigned int> mFreeList[2];

	int mStoreIndex, mUseIndex;

	float mSinTable[3600], mCosTable[3600];

	std::vector<Bullet> mSpawnedBullets; // should be queue

private:

	unsigned int getFreeBulletSlot();

	void killBullet(Bullet* b);

public:

	BulletBattery(bs::Machine* machine);

	int update(float frameTime);

	void render(RendererGL* renderer);

	int getCapacity() const;

	// Scripting
	bs::UserTypeBase* emitAngle(float x, float y, const float* args);

	bs::UserTypeBase* emitTarget(float x, float y, const float* args);

	void killBullet(bs::UserTypeBase* object);

	void setAngle(bs::UserTypeBase* object, float value);

	float getAngle(bs::UserTypeBase* object);

	void setAlpha(bs::UserTypeBase* object, float value);

	float getAlpha(bs::UserTypeBase* object);

	void setRed(bs::UserTypeBase* object, float value);

	float getRed(bs::UserTypeBase* object);

	void setGreen(bs::UserTypeBase* object, float value);

	float getGreen(bs::UserTypeBase* object);

	void setBlue(bs::UserTypeBase* object, float value);

	float getBlue(bs::UserTypeBase* object);

	void gravity(bs::UserTypeBase* object, float frameTime, const float* args);
};

// Function hooks
bs::UserTypeBase* bullet_emitAngle(float x, float y, const float* args);

bs::UserTypeBase* bullet_emitTarget(float x, float y, const float* args);

void bullet_kill(bs::UserTypeBase* object);

void bullet_setAngle(bs::UserTypeBase* object, float value);

float bullet_getAngle(bs::UserTypeBase* object);

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