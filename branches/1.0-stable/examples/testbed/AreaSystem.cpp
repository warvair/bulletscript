#include <iostream>
#include <algorithm>
#include <cmath>
#include "Main.h"
#include "AreaSystem.h"

AreaBattery* g_areas = 0;

bs::UserTypeBase* area_emitQuadC(float x, float y, float angle, const float* args, void* userObj)
{
	return g_areas->emitQuadC(x, y, angle, args, userObj);
}

bs::UserTypeBase* area_emitQuadB(float x, float y, float angle, const float* args, void* userObj)
{
	return g_areas->emitQuadB(x, y, angle, args, userObj);
}

bs::UserTypeBase* area_emitQuadProjected(float x, float y, float angle, const float* args, void* userObj)
{
	return g_areas->emitQuadProjected(x, y, angle, args, userObj);
}

bs::UserTypeBase* area_emitEllipse(float x, float y, float angle, const float* args, void* userObj)
{
	return g_areas->emitEllipse(x, y, angle, args, userObj);
}

bs::UserTypeBase* area_emitArc(float x, float y, float angle, const float* args, void* userObj)
{
	return g_areas->emitArc(x, y, angle, args, userObj);
}

void area_kill(bs::UserTypeBase* object, void* userObj)
{
	g_areas->killArea(object);
}

void area_setX(bs::UserTypeBase* object, float value)
{
	g_areas->setX(object, value);
}

float area_getX(bs::UserTypeBase* object)
{
	return g_areas->getX(object);
}

void area_setY(bs::UserTypeBase* object, float value)
{
	g_areas->setY(object, value);
}

float area_getY(bs::UserTypeBase* object)
{
	return g_areas->getY(object);
}

void area_setAngle(bs::UserTypeBase* object, float value)
{
	g_areas->setAngle(object, value);
}

float area_getAngle(bs::UserTypeBase* object)
{
	return g_areas->getAngle(object);
}
void area_setWidth(bs::UserTypeBase* object, float value)
{
	g_areas->setWidth(object, value);
}

float area_getWidth(bs::UserTypeBase* object)
{
	return g_areas->getWidth(object);
}

void area_setHeight(bs::UserTypeBase* object, float value)
{
	g_areas->setHeight(object, value);
}

float area_getHeight(bs::UserTypeBase* object)
{
	return g_areas->getHeight(object);
}

void area_setInnerWidth(bs::UserTypeBase* object, float value)
{
	g_areas->setInnerWidth(object, value);
}

float area_getInnerWidth(bs::UserTypeBase* object)
{
	return g_areas->getInnerWidth(object);
}

void area_setInnerHeight(bs::UserTypeBase* object, float value)
{
	g_areas->setInnerHeight(object, value);
}

float area_getInnerHeight(bs::UserTypeBase* object)
{
	return g_areas->getInnerHeight(object);
}

void area_setStart(bs::UserTypeBase* object, float value)
{
	g_areas->setStart(object, value);
}

float area_getStart(bs::UserTypeBase* object)
{
	return g_areas->getStart(object);
}

void area_setEnd(bs::UserTypeBase* object, float value)
{
	g_areas->setEnd(object, value);
}

float area_getEnd(bs::UserTypeBase* object)
{
	return g_areas->getEnd(object);
}

void area_setAlpha(bs::UserTypeBase* object, float value)
{
	g_areas->setAlpha(object, value);
}

float area_getAlpha(bs::UserTypeBase* object)
{
	return g_areas->getAlpha(object);
}

// --------------------------------------------------------------------------------
AreaBattery::AreaBattery(bs::Machine* machine) :
	mMachine(machine),
	mStoreIndex(0),
	mUseIndex(1)
{
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
bs::UserTypeBase* AreaBattery::emitQuadC(float x, float y, float angle, const float* args, void* userObj)
{
	Area a;
	a._active = true;
	a._time = 0;
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
bs::UserTypeBase* AreaBattery::emitQuadB(float x, float y, float angle, const float* args, void* userObj)
{
	Area a;
	a._active = true;
	a._time = 0;
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
bs::UserTypeBase* AreaBattery::emitQuadProjected(float x, float y, float angle, const float* args, void* userObj)
{
	Area a;
	a._active = true;
	a._time = 0;
	a.type = AT_QuadProjected;

	a.start = args[-4];

	// Project x and y, 'dist' along the angle
	a.x = x - sin(angle * bs::DEG_TO_RAD) * a.start;
	a.y = y;
	a.w = args[-3];
	a.h = args[-2];
	a.angle = angle + args[-1];
	a.alpha = 1;

	size_t count = mSpawnedAreas.size();
	mSpawnedAreas.push_back(a);

	return &(mSpawnedAreas[count]);
}
// --------------------------------------------------------------------------------
bs::UserTypeBase* AreaBattery::emitEllipse(float x, float y, float angle, const float* args, void* userObj)
{
	Area a;
	a._active = true;
	a._time = 0;
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
bs::UserTypeBase* AreaBattery::emitArc(float x, float y, float angle, const float* args, void* userObj)
{
	Area a;
	a._active = true;
	a._time = 0;
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
	mAreas[a->_index]._active = false;
	mFreeList[mStoreIndex].push_back(a->_index);
	mMachine->releaseType(a);
}
// --------------------------------------------------------------------------------
void AreaBattery::killArea(bs::UserTypeBase* object)
{
	killArea(static_cast<Area*>(object));
}
// --------------------------------------------------------------------------------
void AreaBattery::setX(bs::UserTypeBase* object, float value)
{
	Area* a = static_cast<Area*>(object);
	a->x = value;
}
// --------------------------------------------------------------------------------
float AreaBattery::getX(bs::UserTypeBase* object)
{
	Area* a = static_cast<Area*>(object);
	return a->x;
}
// --------------------------------------------------------------------------------
void AreaBattery::setY(bs::UserTypeBase* object, float value)
{
	Area* a = static_cast<Area*>(object);
	a->y = value;
}
// --------------------------------------------------------------------------------
float AreaBattery::getY(bs::UserTypeBase* object)
{
	Area* a = static_cast<Area*>(object);
	return a->y;
}
// --------------------------------------------------------------------------------
void AreaBattery::setAngle(bs::UserTypeBase* object, float value)
{
	Area* a = static_cast<Area*>(object);
	a->angle = value;
}
// --------------------------------------------------------------------------------
float AreaBattery::getAngle(bs::UserTypeBase* object)
{
	Area* a = static_cast<Area*>(object);
	return a->angle;
}
// --------------------------------------------------------------------------------
void AreaBattery::setWidth(bs::UserTypeBase* object, float value)
{
	Area* a = static_cast<Area*>(object);
	a->w = value;
}
// --------------------------------------------------------------------------------
float AreaBattery::getWidth(bs::UserTypeBase* object)
{
	Area* a = static_cast<Area*>(object);
	return a->w;
}
// --------------------------------------------------------------------------------
void AreaBattery::setHeight(bs::UserTypeBase* object, float value)
{
	Area* a = static_cast<Area*>(object);
	a->h = value;
}
// --------------------------------------------------------------------------------
float AreaBattery::getHeight(bs::UserTypeBase* object)
{
	Area* a = static_cast<Area*>(object);
	return a->h;
}
// --------------------------------------------------------------------------------
void AreaBattery::setInnerWidth(bs::UserTypeBase* object, float value)
{
	Area* a = static_cast<Area*>(object);
	a->innerw = value;
}
// --------------------------------------------------------------------------------
float AreaBattery::getInnerWidth(bs::UserTypeBase* object)
{
	Area* a = static_cast<Area*>(object);
	return a->innerw;
}
// --------------------------------------------------------------------------------
void AreaBattery::setInnerHeight(bs::UserTypeBase* object, float value)
{
	Area* a = static_cast<Area*>(object);
	a->innerh = value;
}
// --------------------------------------------------------------------------------
float AreaBattery::getInnerHeight(bs::UserTypeBase* object)
{
	Area* a = static_cast<Area*>(object);
	return a->innerh;
}
// --------------------------------------------------------------------------------
void AreaBattery::setAlpha(bs::UserTypeBase* object, float value)
{
	Area* a = static_cast<Area*>(object);
	a->alpha = value;
}
// --------------------------------------------------------------------------------
float AreaBattery::getAlpha(bs::UserTypeBase* object)
{
	Area* a = static_cast<Area*>(object);
	return a->alpha;
}
// --------------------------------------------------------------------------------
void AreaBattery::setStart(bs::UserTypeBase* object, float value)
{
	Area* a = static_cast<Area*>(object);
	a->start = value;
}
// --------------------------------------------------------------------------------
float AreaBattery::getStart(bs::UserTypeBase* object)
{
	Area* a = static_cast<Area*>(object);
	return a->start;
}
// --------------------------------------------------------------------------------
void AreaBattery::setEnd(bs::UserTypeBase* object, float value)
{
	Area* a = static_cast<Area*>(object);
	a->end = value;
}
// --------------------------------------------------------------------------------
float AreaBattery::getEnd(bs::UserTypeBase* object)
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
		a._index = index;
		if (a._active)
		{
			a._time += frameTime;

			// areascript: apply affectors and control functions
			mMachine->updateType(&a, a.x, a.y, a.angle, frameTime);

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
		if (a._active)
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
