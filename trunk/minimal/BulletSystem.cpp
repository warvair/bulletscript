#include <cmath>
#include <iostream>
#include <algorithm>
#include "BulletSystem.h"

int gBulletsEmitted = 0;

// --------------------------------------------------------------------------------
// BulletBattery
// --------------------------------------------------------------------------------
std::vector<Bullet> BulletBattery::mBullets;
std::vector<unsigned int> BulletBattery::mFreeList[2];
int BulletBattery::mStoreIndex;
int BulletBattery::mUseIndex;
std::vector<Bullet> BulletBattery::mSpawnedBullets;

// --------------------------------------------------------------------------------
void BulletBattery::initialise()
{
	mStoreIndex = 0;
	mUseIndex = 1;

	mBullets.resize(BATTERY_SIZE);
	mFreeList[mStoreIndex].reserve(BATTERY_SIZE);
	mFreeList[mUseIndex].reserve(BATTERY_SIZE);

	for (int i = 0; i < BATTERY_SIZE; ++ i)
		mFreeList[mUseIndex].push_back (BATTERY_SIZE - i - 1);
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
			std::sort (mFreeList[mStoreIndex].begin(), 
					   mFreeList[mStoreIndex].end(),
					   BulletSorter());
			mStoreIndex = mUseIndex;
			mUseIndex = (mStoreIndex == 0) ? 1 : 0;

			id = mFreeList[mUseIndex].back();
			mFreeList[mUseIndex].pop_back();
		}
		else
		{
			id = (unsigned int) mBullets.size();
			mBullets.push_back (Bullet());
		}
	}

	return id;
}
// --------------------------------------------------------------------------------
Bullet* BulletBattery::emitAngle(BS::bstype x, BS::bstype y, const BS::bstype* args)
{
	std::cout << "fireA " << x << " " << y << " " << args[-3] << std::endl;

	Bullet b;
	b.__active = true;
	b.__time = 0;
	b.stage = 0;
	b.x = x;
	b.y = y;
	b.speed = b.speed0 = args[-2];
	b.damage = args[-1];
	b.vx = (BS::bstype) sin(args[-3] * 0.017453);
	b.vy = (BS::bstype) cos(args[-3] * 0.017453);

	size_t count = mSpawnedBullets.size();
	mSpawnedBullets.push_back(b);

	// Set args used and return bullet
	return &(mSpawnedBullets[count]);
}
// --------------------------------------------------------------------------------
int BulletBattery::update(float frameTime, BS::Machine<Bullet>* machine)
{
	int count = 0;

	// Add recently spawned bullets
	for (size_t i = 0; i < mSpawnedBullets.size(); ++i)
	{
		unsigned int slot = getFreeBulletSlot();
		mBullets[slot] = mSpawnedBullets[i];
		gBulletsEmitted++;
	}

	mSpawnedBullets.clear();

	// And now update all bullets
	for (size_t i = 0; i < mBullets.size(); ++i)
	{
		Bullet* b = &(mBullets[i]);
		if (b->__active)
		{
			b->__time += frameTime;
			
			// Apply normal movement update
			b->x += b->vx * b->speed * frameTime;
			b->y += b->vy * b->speed * frameTime;

			// Apply bulletscript update/control here.
			machine->updateType(b, b->x, b->y, frameTime);

			// No idea why we have to re-acquire here.  STL internal weirdness or something?
			b = &(mBullets[i]);

			// Check for death
			if (b->y < 0 || b->y > 800 || b->x < 0 || b->x > 600)
			{
				mBullets[i].__active = false;
				mFreeList[mStoreIndex].push_back(i);
				machine->releaseType(b);
			}
			else
			{
				count++;
			}
		}
	}

	return count;
}
// --------------------------------------------------------------------------------
