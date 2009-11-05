#include <cmath>
#include <iostream>
#include <algorithm>
#include "Main.h"
#include "BulletSystem.h"
#include "RendererGL.h"

int gTotalBullets = 0;

// --------------------------------------------------------------------------------
// BulletBattery
// --------------------------------------------------------------------------------
bs::Machine* BulletBattery::mMachine = 0;
std::vector<Bullet> BulletBattery::mBullets;
std::vector<unsigned int> BulletBattery::mFreeList[2];
int BulletBattery::mStoreIndex;
int BulletBattery::mUseIndex;
std::vector<Bullet> BulletBattery::mSpawnedBullets;

// --------------------------------------------------------------------------------
void BulletBattery::initialise(bs::Machine* machine)
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
bs::UserTypeBase* BulletBattery::emitAngle(bs::bstype x, bs::bstype y, const bs::bstype* args)
{
	Bullet b;
	b.__active = true;
	b.__time = 0;

	b.x = x;
	b.y = y;
	b.speed = args[-1];
	b.vx = (bs::bstype) sin(args[-2] * bs::DEG_TO_RAD);
	b.vy = (bs::bstype) cos(args[-2] * bs::DEG_TO_RAD);
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
void BulletBattery::setAngle(bs::UserTypeBase* object, bs::bstype value)
{
	Bullet* b = static_cast<Bullet*>(object);

	b->vx = (bs::bstype) sin(value * bs::DEG_TO_RAD);
	b->vy = (bs::bstype) cos(value * bs::DEG_TO_RAD);
}
// --------------------------------------------------------------------------------
bs::bstype BulletBattery::getAngle(bs::UserTypeBase* object)
{
	Bullet* b = static_cast<Bullet*>(object);

	bs::bstype angle = atan2(b->vy, b->vx) * bs::RAD_TO_DEG;
	if (angle < 0)
		return fabs(angle) + 90;
	else
	{
		return (180 - angle) - 90;
	}
}
// --------------------------------------------------------------------------------
void BulletBattery::setFade(bs::UserTypeBase* object, bs::bstype value)
{
	Bullet* b = static_cast<Bullet*>(object);
	b->alpha = value;
}
// --------------------------------------------------------------------------------
bs::bstype BulletBattery::getFade(bs::UserTypeBase* object)
{
	Bullet* b = static_cast<Bullet*>(object);
	return b->alpha;
}
// --------------------------------------------------------------------------------
void BulletBattery::setRed(bs::UserTypeBase* object, bs::bstype value)
{
	Bullet* b = static_cast<Bullet*>(object);
	b->red = value;
}
// --------------------------------------------------------------------------------
bs::bstype BulletBattery::getRed(bs::UserTypeBase* object)
{
	Bullet* b = static_cast<Bullet*>(object);
	return b->red;
}
// --------------------------------------------------------------------------------
void BulletBattery::setGreen(bs::UserTypeBase* object, bs::bstype value)
{
	Bullet* b = static_cast<Bullet*>(object);
	b->green = value;
}
// --------------------------------------------------------------------------------
bs::bstype BulletBattery::getGreen(bs::UserTypeBase* object)
{
	Bullet* b = static_cast<Bullet*>(object);
	return b->green;
}
// --------------------------------------------------------------------------------
void BulletBattery::setBlue(bs::UserTypeBase* object, bs::bstype value)
{
	Bullet* b = static_cast<Bullet*>(object);
	b->blue = value;
}
// --------------------------------------------------------------------------------
bs::bstype BulletBattery::getBlue(bs::UserTypeBase* object)
{
	Bullet* b = static_cast<Bullet*>(object);
	return b->blue;
}
// --------------------------------------------------------------------------------
void BulletBattery::gravity(bs::UserTypeBase* object, float frameTime, const bs::bstype* args)
{
	Bullet* b = static_cast<Bullet*>(object);
//	b->y -= args[-1] * frameTime;
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
			renderer->addBullet(b);

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