#include <cmath>
#include <iostream>
#include <algorithm>
#include "Main.h"
#include "BulletSystem.h"
#include "RendererGL.h"

BulletBattery* g_bullets = 0;

bs::UserTypeBase* bullet_emitAngle(float x, float y, float angle, const float* args, void* userObj)
{
	return g_bullets->emitAngle(x, y, angle, args, userObj);
}

bs::UserTypeBase* bullet_emitTarget(float x, float y, float angle, const float* args, void* userObj)
{
	return g_bullets->emitTarget(x, y, angle, args, userObj);
}

void bullet_kill(bs::UserTypeBase* object, void* userObj)
{
	g_bullets->killBullet(object);
}

void bullet_setX(bs::UserTypeBase* object, float value)
{
	g_bullets->setX(object, value);
}

float bullet_getX(bs::UserTypeBase* object)
{
	return g_bullets->getX(object);
}

void bullet_setY(bs::UserTypeBase* object, float value)
{
	g_bullets->setY(object, value);
}

float bullet_getY(bs::UserTypeBase* object)
{
	return g_bullets->getY(object);
}

void bullet_setAngle(bs::UserTypeBase* object, float value)
{
	g_bullets->setAngle(object, value);
}

float bullet_getAngle(bs::UserTypeBase* object)
{
	return g_bullets->getAngle(object);
}

void bullet_setSpeed(bs::UserTypeBase* object, float value)
{
	g_bullets->setSpeed(object, value);
}

float bullet_getSpeed(bs::UserTypeBase* object)
{
	return g_bullets->getSpeed(object);
}

void bullet_setRed(bs::UserTypeBase* object, float value)
{
	g_bullets->setRed(object, value);
}

float bullet_getRed(bs::UserTypeBase* object)
{
	return g_bullets->getRed(object);
}

void bullet_setGreen(bs::UserTypeBase* object, float value)
{
	g_bullets->setGreen(object, value);
}

float bullet_getGreen(bs::UserTypeBase* object)
{
	return g_bullets->getGreen(object);
}

void bullet_setBlue(bs::UserTypeBase* object, float value)
{
	g_bullets->setBlue(object, value);
}

float bullet_getBlue(bs::UserTypeBase* object)
{
	return g_bullets->getBlue(object);
}

void bullet_setAlpha(bs::UserTypeBase* object, float value)
{
	g_bullets->setAlpha(object, value);
}

float bullet_getAlpha(bs::UserTypeBase* object)
{
	return g_bullets->getAlpha(object);
}

void bullet_gravity(bs::UserTypeBase* object, float frameTime, const float* args)
{
	g_bullets->gravity(object, frameTime, args);
}

// --------------------------------------------------------------------------------
BulletBattery::BulletBattery(bs::Machine* machine) :
	mMachine(machine),
	mStoreIndex(0),
	mUseIndex(1)
{
	mBullets.resize(BATTERY_SIZE);
	mFreeList[mStoreIndex].reserve(BATTERY_SIZE);
	mFreeList[mUseIndex].reserve(BATTERY_SIZE);

	for (int i = 0; i < BATTERY_SIZE; ++ i)
		mFreeList[mUseIndex].push_back(BATTERY_SIZE - i - 1);

	// trig tables
	for (int i = 0; i < 3600; ++i)
	{
		mSinTable[i] = (float) sin((i / 10.0f) * bs::DEG_TO_RAD);
		mCosTable[i] = (float) cos((i / 10.0f) * bs::DEG_TO_RAD);
	}
}
// --------------------------------------------------------------------------------
unsigned int BulletBattery::getFreeBulletSlot()
{
	unsigned int id;

	if (mFreeList[mUseIndex].size())
	{
		id = mFreeList[mUseIndex].back();
		mFreeList[mUseIndex].pop_back();
	}
	else
	{
		if (mFreeList[mStoreIndex].size())
		{
			std::sort(mFreeList[mStoreIndex].begin(), 
					  mFreeList[mStoreIndex].end(),
					  BulletSorter());

			mStoreIndex = mUseIndex;
			mUseIndex = (mStoreIndex == 0) ? 1 : 0;

			id = mFreeList[mUseIndex].back ();
			mFreeList[mUseIndex].pop_back ();
		}
		else
		{
			id = (unsigned int) mBullets.size();
			mBullets.push_back(Bullet());
		}
	}

	return id;
}
// --------------------------------------------------------------------------------
int BulletBattery::getCapacity() const
{
	return (int) mBullets.capacity();
}
// --------------------------------------------------------------------------------
bs::UserTypeBase* BulletBattery::emitAngle(float x, float y, float angle, const float* args, void* user)
{
	Bullet b;
	b.__active = true;
	b.__time = 0;

	b.x = x;
	b.y = y;
	b.speed = args[-1];
	b.angle = args[-2];
	if (b.angle < 0.0f)
		b.angle += 360.0f;

	int index = (int) (b.angle * 10) % 3600;
	b.vx = mSinTable[index] * args[-1];
	b.vy = mCosTable[index] * args[-1];

	b.alpha = 1;
	b.red = 1;
	b.green = 1;
	b.blue = 1;

	size_t count = mSpawnedBullets.size();
	mSpawnedBullets.push_back(b);

	return &(mSpawnedBullets[count]);
}
// --------------------------------------------------------------------------------
bs::UserTypeBase* BulletBattery::emitTarget(float x, float y, float angle, const float* args, void* user)
{
	Bullet b;
	b.__active = true;
	b.__time = 0;

	b.x = x;
	b.y = y;
	b.speed = args[-1];

	float dx = args[-4] - x;
	float dy = args[-3] - y;
	float tgtAngle = (float) atan2(dy, -dx) * bs::RAD_TO_DEG - 90.0f + args[-2];
	if (tgtAngle < 0.0f)
		tgtAngle += 360.0f;
	b.angle = tgtAngle;

	int index = (int) (tgtAngle * 10) % 3600;
	b.vx = mSinTable[index] * args[-1];
	b.vy = mCosTable[index] * args[-1];

	b.alpha = 1;
	b.red = 1;
	b.green = 1;
	b.blue = 1;

	size_t count = mSpawnedBullets.size();
	mSpawnedBullets.push_back(b);

	return &(mSpawnedBullets[count]);
}
// --------------------------------------------------------------------------------
void BulletBattery::killBullet(Bullet* b)
{
	mBullets[b->__index].__active = false;
	mFreeList[mStoreIndex].push_back(b->__index);
	mMachine->releaseType(b);
}
// --------------------------------------------------------------------------------
void BulletBattery::killBullet(bs::UserTypeBase* object)
{
	killBullet(static_cast<Bullet*>(object));
}
// --------------------------------------------------------------------------------
void BulletBattery::setX(bs::UserTypeBase* object, float value)
{
	Bullet* b = static_cast<Bullet*>(object);
	b->x = value;
}
// --------------------------------------------------------------------------------
float BulletBattery::getX(bs::UserTypeBase* object)
{
	Bullet* b = static_cast<Bullet*>(object);
	return b->x;
}
// --------------------------------------------------------------------------------
void BulletBattery::setY(bs::UserTypeBase* object, float value)
{
	Bullet* b = static_cast<Bullet*>(object);
	b->y = value;
}
// --------------------------------------------------------------------------------
float BulletBattery::getY(bs::UserTypeBase* object)
{
	Bullet* b = static_cast<Bullet*>(object);
	return b->y;
}
// --------------------------------------------------------------------------------
void BulletBattery::setAngle(bs::UserTypeBase* object, float value)
{
	Bullet* b = static_cast<Bullet*>(object);

	b->angle = value;

	if (value < 0.0f)
		value += 360.0f;

	int index = (int) (value * 10) % 3600;
	b->vx = mSinTable[index] * b->speed;
	b->vy = mCosTable[index] * b->speed;
}
// --------------------------------------------------------------------------------
float BulletBattery::getAngle(bs::UserTypeBase* object)
{
	Bullet* b = static_cast<Bullet*>(object);
	return b->angle;
}
// --------------------------------------------------------------------------------
void BulletBattery::setSpeed(bs::UserTypeBase* object, float value)
{
	Bullet* b = static_cast<Bullet*>(object);

	b->speed = value;
	int index = (int) (b->angle * 10) % 3600;
	b->vx = mSinTable[index] * value;
	b->vy = mCosTable[index] * value;
}
// --------------------------------------------------------------------------------
float BulletBattery::getSpeed(bs::UserTypeBase* object)
{
	Bullet* b = static_cast<Bullet*>(object);
	return b->speed;
}
// --------------------------------------------------------------------------------
void BulletBattery::setAlpha(bs::UserTypeBase* object, float value)
{
	Bullet* b = static_cast<Bullet*>(object);
	b->alpha = value;
}
// --------------------------------------------------------------------------------
float BulletBattery::getAlpha(bs::UserTypeBase* object)
{
	Bullet* b = static_cast<Bullet*>(object);
	return b->alpha;
}
// --------------------------------------------------------------------------------
void BulletBattery::setRed(bs::UserTypeBase* object, float value)
{
	Bullet* b = static_cast<Bullet*>(object);
	b->red = value;
}
// --------------------------------------------------------------------------------
float BulletBattery::getRed(bs::UserTypeBase* object)
{
	Bullet* b = static_cast<Bullet*>(object);
	return b->red;
}
// --------------------------------------------------------------------------------
void BulletBattery::setGreen(bs::UserTypeBase* object, float value)
{
	Bullet* b = static_cast<Bullet*>(object);
	b->green = value;
}
// --------------------------------------------------------------------------------
float BulletBattery::getGreen(bs::UserTypeBase* object)
{
	Bullet* b = static_cast<Bullet*>(object);
	return b->green;
}
// --------------------------------------------------------------------------------
void BulletBattery::setBlue(bs::UserTypeBase* object, float value)
{
	Bullet* b = static_cast<Bullet*>(object);
	b->blue = value;
}
// --------------------------------------------------------------------------------
float BulletBattery::getBlue(bs::UserTypeBase* object)
{
	Bullet* b = static_cast<Bullet*>(object);
	return b->blue;
}
// --------------------------------------------------------------------------------
void BulletBattery::gravity(bs::UserTypeBase* object, float frameTime, const float* args)
{
	Bullet* b = static_cast<Bullet*>(object);

	b->vy -= args[-1] * frameTime;
}
// --------------------------------------------------------------------------------
int BulletBattery::update(float frameTime)
{
	// Add recently spawned bullets
	for (size_t i = 0; i < mSpawnedBullets.size(); ++i)
	{
		unsigned int slot = getFreeBulletSlot(); // UserTypeBase relocation occurs here
		mBullets[slot] = mSpawnedBullets[i];
	}

	mSpawnedBullets.clear();

	int index = 0;
	int count = 0;
	std::vector<Bullet>::iterator it = mBullets.begin();
	while (it != mBullets.end())
	{
		Bullet &b = *it;
		b.__index = index;
		if (b.__active)
		{
			b.__time += frameTime;
			
			// Apply normal movement update
			b.x += b.vx * frameTime;
			b.y += b.vy * frameTime;

			// bulletscript: apply affectors and control functions
			mMachine->updateType(&b, b.x, b.y, b.angle, frameTime);


			// Check for death
			if (b.y < 0 || b.y > SCREEN_HEIGHT || b.x < 0 || b.x > SCREEN_WIDTH)
				killBullet(&b);
			else
				count++;
		}

		++it;
		++index;
	}

	return count;
}
// --------------------------------------------------------------------------------
void BulletBattery::render(RendererGL *renderer)
{
#ifndef MINIMAL_APP
	std::vector<Bullet>::iterator it = mBullets.begin();
	while (it != mBullets.end ())
	{
		Bullet &b = *it;
		if (b.__active)
			renderer->addBullet(b);

		++ it;
	}
#endif
}
// --------------------------------------------------------------------------------
