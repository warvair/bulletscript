#include <cmath>
#include <iostream>
#include <algorithm>
#include "Main.h"
#include "BulletSystem.h"

int gTotalBullets = 0;

// --------------------------------------------------------------------------------
// BulletBattery
// --------------------------------------------------------------------------------
BS::Machine<Bullet>* BulletBattery::mMachine = 0;
std::vector<Bullet> BulletBattery::mBullets;
std::vector<unsigned int> BulletBattery::mFreeList[2];
int BulletBattery::mStoreIndex;
int BulletBattery::mUseIndex;
std::vector<Bullet> BulletBattery::mSpawnedBullets;

// --------------------------------------------------------------------------------
void BulletBattery::initialise(BS::Machine<Bullet>* machine)
{
	mMachine = machine;
	
	mStoreIndex = 0;
	mUseIndex = 1;

	mBullets.resize(BATTERY_SIZE);
	mFreeList[mStoreIndex].reserve(BATTERY_SIZE);
	mFreeList[mUseIndex].reserve(BATTERY_SIZE);

	for (int i = 0; i < BATTERY_SIZE; ++ i)
		mFreeList[mUseIndex].push_back(BATTERY_SIZE - i - 1);
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
Bullet* BulletBattery::emitAngle(BS::bstype x, BS::bstype y, const BS::bstype* args)
{
	Bullet b;
	b.__active = true;
	b.__time = 0;

	b.x = x;
	b.y = y;
	b.speed = args[-1];
	b.vx = (BS::bstype) sin(args[-2] * BS::DEG_TO_RAD);
	b.vy = (BS::bstype) cos(args[-2] * BS::DEG_TO_RAD);
	b.fade = 1;

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
void BulletBattery::killBullet(void* object)
{
	killBullet(static_cast<Bullet*>(object));
}
// --------------------------------------------------------------------------------
void BulletBattery::setAngle(void* object, BS::bstype value)
{
	Bullet* b = static_cast<Bullet*>(object);

	b->vx = (BS::bstype) sin(value * BS::DEG_TO_RAD);
	b->vy = (BS::bstype) cos(value * BS::DEG_TO_RAD);
}
// --------------------------------------------------------------------------------
BS::bstype BulletBattery::getAngle(void* object)
{
	Bullet* b = static_cast<Bullet*>(object);

	BS::bstype angle = atan2(b->vy, b->vx) * BS::RAD_TO_DEG;
	if (angle < 0)
		return fabs(angle) + 90;
	else
	{
		return (180 - angle) - 90;
	}
}
// --------------------------------------------------------------------------------
void BulletBattery::setFade(void* object, BS::bstype value)
{
	Bullet* b = static_cast<Bullet*>(object);
	b->fade = value;
}
// --------------------------------------------------------------------------------
BS::bstype BulletBattery::getFade(void* object)
{
	Bullet* b = static_cast<Bullet*>(object);
	return b->fade;
}
// --------------------------------------------------------------------------------
int BulletBattery::update(float frameTime)
{
	// Add recently spawned bullets
	for (size_t i = 0; i < mSpawnedBullets.size(); ++i)
	{
		unsigned int slot = getFreeBulletSlot();
		mBullets[slot] = mSpawnedBullets[i];
		gTotalBullets++;
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
			b.x += b.vx * b.speed * frameTime;
			b.y += b.vy * b.speed * frameTime;

			// bulletscript: apply affectors and control functions
			mMachine->updateType(&b, b.x, b.y, frameTime);

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
	std::vector<Bullet>::iterator it = mBullets.begin();
	while (it != mBullets.end ())
	{
		Bullet &b = *it;
		if (b.__active)
			renderer->addBullet(b.x, b.y, b.fade);

		++ it;
	}
}
// --------------------------------------------------------------------------------
Bullet* BulletBattery::getBullet(int index)
{
	return &(mBullets[index]);
}
// --------------------------------------------------------------------------------
int BulletBattery::getNumBullets()
{
	return mBullets.size();
}
// --------------------------------------------------------------------------------