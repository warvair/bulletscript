#include <iostream>
#include <algorithm>
#include "Main.h"
#include "AreaSystem.h"

// --------------------------------------------------------------------------------
// AreaBattery
// --------------------------------------------------------------------------------
BS::Machine<Bullet, Area>* AreaBattery::mMachine = 0;
std::vector<Area> AreaBattery::mAreas;
std::vector<unsigned int> AreaBattery::mFreeList[2];
int AreaBattery::mStoreIndex;
int AreaBattery::mUseIndex;
std::vector<Area> AreaBattery::mSpawnedAreas;

// --------------------------------------------------------------------------------
void AreaBattery::initialise(BS::Machine<Bullet, Area>* machine)
{
	mMachine = machine;
	
	mStoreIndex = 0;
	mUseIndex = 1;

	mAreas.resize(BATTERY_SIZE);
	mFreeList[mStoreIndex].reserve(BATTERY_SIZE);
	mFreeList[mUseIndex].reserve(BATTERY_SIZE);

	for (int i = 0; i < BATTERY_SIZE; ++ i)
		mFreeList[mUseIndex].push_back(BATTERY_SIZE - i - 1);
}
// --------------------------------------------------------------------------------
unsigned int AreaBattery::getFreeAreaSlot()
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
					  AreaSorter());

			mStoreIndex = mUseIndex;
			mUseIndex = (mStoreIndex == 0) ? 1 : 0;

			id = mFreeList[mUseIndex].back ();
			mFreeList[mUseIndex].pop_back ();
		}
		else
		{
			id = (unsigned int) mAreas.size();
			mAreas.push_back(Area());
		}
	}

	return id;
}
// --------------------------------------------------------------------------------
Area* AreaBattery::emitQuadC(BS::bstype x, BS::bstype y, const BS::bstype* args)
{
	Area a;
	a.__active = true;
	a.__time = 0;
	a.type = AT_QuadCentred;

	a.x = x;
	a.y = y;
	a.w = args[-3];
	a.h = args[-2];
	a.angle = args[-1];
	a.fade = 1;

	size_t count = mSpawnedAreas.size();
	mSpawnedAreas.push_back(a);

	return &(mSpawnedAreas[count]);
}
// --------------------------------------------------------------------------------
Area* AreaBattery::emitQuadB(BS::bstype x, BS::bstype y, const BS::bstype* args)
{
	Area a;
	a.__active = true;
	a.__time = 0;
	a.type = AT_QuadBased;

	a.x = x;
	a.y = y;
	a.w = args[-3];
	a.h = args[-2];
	a.angle = args[-1];
	a.fade = 1;

	size_t count = mSpawnedAreas.size();
	mSpawnedAreas.push_back(a);

	return &(mSpawnedAreas[count]);
}
// --------------------------------------------------------------------------------
Area* AreaBattery::emitEllipse(BS::bstype x, BS::bstype y, const BS::bstype* args)
{
	Area a;
	a.__active = true;
	a.__time = 0;
	a.type = AT_Ellipse;

	a.x = x;
	a.y = y;
	a.w = args[-2];
	a.h = args[-1];
	a.fade = 1;

	size_t count = mSpawnedAreas.size();
	mSpawnedAreas.push_back(a);

	return &(mSpawnedAreas[count]);
}
// --------------------------------------------------------------------------------
void AreaBattery::killArea(Area* a)
{
	mAreas[a->__index].__active = false;
	mFreeList[mStoreIndex].push_back(a->__index);
	mMachine->releaseType(a);
}
// --------------------------------------------------------------------------------
void AreaBattery::killArea(void* object)
{
	killArea(static_cast<Area*>(object));
}
// --------------------------------------------------------------------------------
void AreaBattery::setWidth(void* object, BS::bstype value)
{
	Area* a = static_cast<Area*>(object);
	a->w = value;
}
// --------------------------------------------------------------------------------
BS::bstype AreaBattery::getWidth(void* object)
{
	Area* a = static_cast<Area*>(object);
	return a->w;
}
// --------------------------------------------------------------------------------
void AreaBattery::setHeight(void* object, BS::bstype value)
{
	Area* a = static_cast<Area*>(object);
	a->h = value;
}
// --------------------------------------------------------------------------------
BS::bstype AreaBattery::getHeight(void* object)
{
	Area* a = static_cast<Area*>(object);
	return a->h;
}
// --------------------------------------------------------------------------------
void AreaBattery::setAngle(void* object, BS::bstype value)
{
	Area* a = static_cast<Area*>(object);
	a->angle = value;
}
// --------------------------------------------------------------------------------
BS::bstype AreaBattery::getAngle(void* object)
{
	Area* a = static_cast<Area*>(object);
	return a->angle;
}
// --------------------------------------------------------------------------------
void AreaBattery::setFade(void* object, BS::bstype value)
{
	Area* a = static_cast<Area*>(object);
	a->fade = value;
}
// --------------------------------------------------------------------------------
BS::bstype AreaBattery::getFade(void* object)
{
	Area* a = static_cast<Area*>(object);
	return a->fade;
}
// --------------------------------------------------------------------------------
int AreaBattery::update(float frameTime)
{
	// Add recently spawned Areas
	for (size_t i = 0; i < mSpawnedAreas.size(); ++i)
	{
		unsigned int slot = getFreeAreaSlot();
		mAreas[slot] = mSpawnedAreas[i];
	}

	mSpawnedAreas.clear();

	int index = 0;
	int count = 0;
	std::vector<Area>::iterator it = mAreas.begin();
	while (it != mAreas.end())
	{
		Area &a = *it;
		a.__index = index;
		if (a.__active)
		{
			a.__time += frameTime;

			// No special movement for areas
			// ...

			// Areascript: apply affectors and control functions
			mMachine->updateType(&a, a.x, a.y, frameTime);

			// Check for death
			if ((a.y + a.h) < 0 || (a.y - a.h) > SCREEN_HEIGHT || (a.x + a.w) < 0 || (a.x - a.w) > SCREEN_WIDTH)
				killArea(&a);
			else
				count++;
		}

		++it;
		++index;
	}

	return count;
}
// --------------------------------------------------------------------------------
void AreaBattery::render(RendererGL *renderer)
{
	std::vector<Area>::iterator it = mAreas.begin();
	while (it != mAreas.end ())
	{
		Area &a = *it;
		if (a.__active)
		{
			if (a.type == AT_Ellipse)
				renderer->addEllipseArea(&a);
			else
				renderer->addQuadArea(&a);
		}

		++ it;
	}
}
// --------------------------------------------------------------------------------
