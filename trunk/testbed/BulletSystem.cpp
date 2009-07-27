#include <cmath>
#include <iostream>
#include <algorithm>
#include "BulletSystem.h"
#include "Ship.h"

// --------------------------------------------------------------------------------
// BulletAffector functions
// --------------------------------------------------------------------------------
void BulletAffector_Accel(Bullet &b, const float *args, float frameTime)
{
	// Change velocity
	float newSpeed = sqrt(args[0] * args[0] + args[1] * args[1]);
	b.speed += newSpeed * frameTime;
	
	b.vx += ((args[0] / newSpeed) - b.vx) / (2.0f / frameTime);
	b.vy += ((args[1] / newSpeed) - b.vy) / (2.0f / frameTime);
}
// --------------------------------------------------------------------------------
void BulletAffector_Force(Bullet &b, const float *args, float frameTime)
{
	b.x += args[0];
	b.y += args[1];
}
// --------------------------------------------------------------------------------
void BulletAffector_DelayAccel(Bullet &b, const float *args, float frameTime)
{
	// After a set time, change speed
	if (b.__time > args[1])
	{
		float dt =(b.__time - args[1]) / (args[2] - args[1]); 
		if (dt >= 1.0f)
			b.speed = args[0];
		else
			b.speed = b.speed0 + (args[0] - b.speed0) * dt;
	}
}
// --------------------------------------------------------------------------------
void BulletAffector_Explode(Bullet &b, const float *args, float frameTime)
{
	if (b.stage == 0 && b.__time > args[0])
	{
		// random angle
		b.stage = 1;
		float newAngle = (float) 110 + (rand() % 140);
		b.vx = (float) sin (newAngle * 0.017453);
		b.vy = (float) cos (newAngle * 0.017453);
		b.speed = args[1];
	}
}
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// BulletBattery
// --------------------------------------------------------------------------------
std::vector<Bullet> BulletBattery::mBullets;
std::vector<unsigned int> BulletBattery::mFreeList[2];
int BulletBattery::mStoreIndex;
int BulletBattery::mUseIndex;

// --------------------------------------------------------------------------------
void BulletBattery::initialise()
{
	mStoreIndex = 0;
	mUseIndex = 1;

	mBullets.resize (BATTERY_SIZE);
	mFreeList[mStoreIndex].reserve (BATTERY_SIZE);
	mFreeList[mUseIndex].reserve (BATTERY_SIZE);

	for (int i = 0; i < BATTERY_SIZE; ++ i)
		mFreeList[mUseIndex].push_back (BATTERY_SIZE - i - 1);
}
// --------------------------------------------------------------------------------
unsigned int BulletBattery::getFreeBulletSlot()
{
	unsigned int id;

	if (mFreeList[mUseIndex].size ())
	{
		id = mFreeList[mUseIndex].back ();
		mFreeList[mUseIndex].pop_back ();
	}
	else
	{
		if (mFreeList[mStoreIndex].size ())
		{
			std::sort (mFreeList[mStoreIndex].begin (), 
					   mFreeList[mStoreIndex].end (),
					   BulletSorter ());
			mStoreIndex = mUseIndex;
			mUseIndex = (mStoreIndex == 0) ? 1 : 0;

			id = mFreeList[mUseIndex].back ();
			mFreeList[mUseIndex].pop_back ();
		}
		else
		{
			id = (unsigned int) mBullets.size ();
			mBullets.push_back (Bullet());
		}
	}

	return id;
}
// --------------------------------------------------------------------------------
int BulletBattery::emitAngle(BS::BulletGunBase *gun, float x, float y, const float* args)
{
//	BulletShip* ship = static_cast<BulletShip*>(gun->getUserObject());
//	ship->emitAngleBullet(x, y, UINT32_TO_FLOAT(args[-3]), UINT32_TO_FLOAT(args[-2]), UINT32_TO_FLOAT(args[-1]));
		
	int slot = getFreeBulletSlot();

	Bullet &b = mBullets[slot];
	b.__active = true;
	b.__time = 0.0f;
	b.__gun = gun;
	b.stage = 0;
	b.x = x;
	b.y = y;
	b.speed = b.speed0 = args[-2];
	b.damage = UINT32_TO_FLOAT(args[-1]);
	b.vx = (float) sin(args[-3] * 0.017453);
	b.vy = (float) cos(args[-3] * 0.017453);

	// Return the number of arguments used
	return 3;
}
// --------------------------------------------------------------------------------
int BulletBattery::emitTarget(BS::BulletGunBase *gun, float x, float y, const float *args)
{
	int slot = getFreeBulletSlot();

	// Calculate angle based on x, y and angle, for targeting a position with an offset of 'angle'
	float dx = args[-5] - x;
	float dy = args[-4] - y;
	float angle = (float) (atan2(dy, -dx) - 1.57) + args[-3] * 0.017453f;

	Bullet &b = mBullets[slot];
	b.__active = true;
	b.__time = 0.0f;
	b.__gun = gun;
	b.stage = 0;
	b.x = x;
	b.y = y;
	b.speed = b.speed0 = args[-2];
	b.damage = args[-1];
	b.vx = (float) sin(angle);
	b.vy = (float) cos(angle);

	// Return the number of arguments used
	return 5;
}
// --------------------------------------------------------------------------------
int BulletBattery::update(float frameTime, BS::BulletMachine<Bullet>* bulletMachine)
{
	int index = 0;
	int count = 0;
	std::vector<Bullet>::iterator it = mBullets.begin ();
	while (it != mBullets.end ())
	{
		Bullet &b = *it;
		if (b.__active)
		{
			b.__time += frameTime;
			
			// Apply normal movement update
			b.x += b.vx * b.speed * frameTime;
			b.y += b.vy * b.speed * frameTime;

			bulletMachine->applyBulletAffectors(b.__gun, b, frameTime);

			// Check for death
			if (b.y < 0 || b.y > 600 || b.x < 0 || b.x > 800)
			{
				mBullets[index].__active = false;
				mFreeList[mStoreIndex].push_back(index);
			}
			else
			{
				count++;
			}
		}

		++it;
		++index;
	}

	return count;
}
// --------------------------------------------------------------------------------
void BulletBattery::render(RendererGL *renderer)
{
	std::vector<Bullet>::iterator it = mBullets.begin ();
	while (it != mBullets.end ())
	{
		Bullet &b = *it;
		if (b.__active)
		{
			renderer->addBullet (b.x, b.y);
		}

		++ it;
	}
}
// --------------------------------------------------------------------------------