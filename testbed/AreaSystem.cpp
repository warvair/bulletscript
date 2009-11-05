#include <iostream>
#include <algorithm>
#include "Main.h"
#include "AreaSystem.h"

// --------------------------------------------------------------------------------
// AreaBattery
// --------------------------------------------------------------------------------
bs::Machine* AreaBattery::mMachine = 0;
std::vector<Area> AreaBattery::mAreas;
std::vector<unsigned int> AreaBattery::mFreeList[2];
int AreaBattery::mStoreIndex;
int AreaBattery::mUseIndex;
std::vector<Area> AreaBattery::mSpawnedAreas;

// --------------------------------------------------------------------------------
void AreaBattery::initialise(bs::Machine* machine)
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
bs::UserTypeBase* AreaBattery::emitQuadC(bs::bstype x, bs::bstype y, const bs::bstype* args)
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
	a.start = 0.0f;
	a.end = 0.0f;
	a.alpha = 1;

	size_t count = mSpawnedAreas.size();
	mSpawnedAreas.push_back(a);

	return &(mSpawnedAreas[count]);
}
// --------------------------------------------------------------------------------
bs::UserTypeBase* AreaBattery::emitQuadB(bs::bstype x, bs::bstype y, const bs::bstype* args)
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
	a.start = 0.0f;
	a.end = 0.0f;
	a.alpha = 1;

	size_t count = mSpawnedAreas.size();
	mSpawnedAreas.push_back(a);

	return &(mSpawnedAreas[count]);
}
// --------------------------------------------------------------------------------
bs::UserTypeBase* AreaBattery::emitEllipse(bs::bstype x, bs::bstype y, const bs::bstype* args)
{
	Area a;
	a.__active = true;
	a.__time = 0;
	a.type = AT_Ellipse;

	a.x = x;
	a.y = y;
	a.w = args[-2];
	a.h = args[-1];
	a.angle = 0.0f;
	a.start = 0.0f;
	a.end = 360.0f;
	a.alpha = 1;

	size_t count = mSpawnedAreas.size();
	mSpawnedAreas.push_back(a);

	return &(mSpawnedAreas[count]);
}
// --------------------------------------------------------------------------------
bs::UserTypeBase* AreaBattery::emitArc(bs::bstype x, bs::bstype y, const bs::bstype* args)
{
	Area a;
	a.__active = true;
	a.__time = 0;
	a.type = AT_Arc;

	a.x = x;
	a.y = y;
	a.w = args[-5];
	a.h = args[-4];
	a.angle = 0.0f;
	a.start = args[-3];
	a.end = args[-2];
	a.innerh = a.innerw = args[-1];
	a.alpha = 1;

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
void AreaBattery::killArea(bs::UserTypeBase* object)
{
	killArea(static_cast<Area*>(object));
}
// --------------------------------------------------------------------------------
void AreaBattery::setWidth(bs::UserTypeBase* object, bs::bstype value)
{
	Area* a = static_cast<Area*>(object);
	a->w = value;
}
// --------------------------------------------------------------------------------
bs::bstype AreaBattery::getWidth(bs::UserTypeBase* object)
{
	Area* a = static_cast<Area*>(object);
	return a->w;
}
// --------------------------------------------------------------------------------
void AreaBattery::setHeight(bs::UserTypeBase* object, bs::bstype value)
{
	Area* a = static_cast<Area*>(object);
	a->h = value;
}
// --------------------------------------------------------------------------------
bs::bstype AreaBattery::getHeight(bs::UserTypeBase* object)
{
	Area* a = static_cast<Area*>(object);
	return a->h;
}
// --------------------------------------------------------------------------------
void AreaBattery::setInnerWidth(bs::UserTypeBase* object, bs::bstype value)
{
	Area* a = static_cast<Area*>(object);
	a->innerw = value;
}
// --------------------------------------------------------------------------------
bs::bstype AreaBattery::getInnerWidth(bs::UserTypeBase* object)
{
	Area* a = static_cast<Area*>(object);
	return a->innerw;
}
// --------------------------------------------------------------------------------
void AreaBattery::setInnerHeight(bs::UserTypeBase* object, bs::bstype value)
{
	Area* a = static_cast<Area*>(object);
	a->innerh = value;
}
// --------------------------------------------------------------------------------
bs::bstype AreaBattery::getInnerHeight(bs::UserTypeBase* object)
{
	Area* a = static_cast<Area*>(object);
	return a->innerh;
}
// --------------------------------------------------------------------------------
void AreaBattery::setAngle(bs::UserTypeBase* object, bs::bstype value)
{
	Area* a = static_cast<Area*>(object);
	a->angle = value;
}
// --------------------------------------------------------------------------------
bs::bstype AreaBattery::getAngle(bs::UserTypeBase* object)
{
	Area* a = static_cast<Area*>(object);
	return a->angle;
}
// --------------------------------------------------------------------------------
void AreaBattery::setFade(bs::UserTypeBase* object, bs::bstype value)
{
	Area* a = static_cast<Area*>(object);
	a->alpha = value;
}
// --------------------------------------------------------------------------------
bs::bstype AreaBattery::getFade(bs::UserTypeBase* object)
{
	Area* a = static_cast<Area*>(object);
	return a->alpha;
}
// --------------------------------------------------------------------------------
void AreaBattery::setStart(bs::UserTypeBase* object, bs::bstype value)
{
	Area* a = static_cast<Area*>(object);
	a->start = value;
}
// --------------------------------------------------------------------------------
bs::bstype AreaBattery::getStart(bs::UserTypeBase* object)
{
	Area* a = static_cast<Area*>(object);
	return a->start;
}
// --------------------------------------------------------------------------------
void AreaBattery::setEnd(bs::UserTypeBase* object, bs::bstype value)
{
	Area* a = static_cast<Area*>(object);
	a->end = value;
}
// --------------------------------------------------------------------------------
bs::bstype AreaBattery::getEnd(bs::UserTypeBase* object)
{
	Area* a = static_cast<Area*>(object);
	return a->end;
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

			// Bulletscript: apply affectors and control functions
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
			else if (a.type == AT_Arc)
				renderer->addArcArea(&a);
			else
				renderer->addQuadArea(&a);
		}

		++ it;
	}
}
// --------------------------------------------------------------------------------
