#ifndef __AREASYSTEM_H__
#define __AREASYSTEM_H__

#include "bsBulletScript.h"
#include "RendererGL.h"

// Areas are either quads or circles.
enum AreaType
{
	AT_QuadCentred,
	AT_QuadBased,
	AT_Ellipse,
	AT_Arc
};

struct Area : public bs::UserTypeBase
{
	int type;			// quad or ellipse
	float x, y;
	float w, h;			// width, height.  Also used for ellipse
	float angle;
	float start, end;	// generic, can be used for arcs
	float innerw, innerh;
	float alpha;

	// Internal variables, do not modify in affector function!
	int __index;
	float __time;

	bool __active;
	char padding[7]; // pad to 64 bytes

	Area() : __active(false) {}
};

class AreaBattery
{
	struct AreaSorter
	{
		bool operator ()(int a, int b)
		{
			return a > b;
		}
	};

	static const int BATTERY_SIZE = 128;

	bs::Machine* mMachine;

	std::vector<Area> mAreas;

	std::vector<unsigned int> mFreeList[2];

	int mStoreIndex, mUseIndex;

	std::vector<Area> mSpawnedAreas;

private:

	unsigned int getFreeAreaSlot();

	void killArea(Area* a);
	
public:

	AreaBattery(bs::Machine* machine);

	int update(float frameTime);

	void render(RendererGL* renderer);

	// Scripting
	bs::UserTypeBase* emitQuadC(float x, float y, const float* args, void* userObj);

	bs::UserTypeBase* emitQuadB(float x, float y, const float* args, void* userObj);

	bs::UserTypeBase* emitEllipse(float x, float y, const float* args, void* userObj);

	bs::UserTypeBase* emitArc(float x, float y, const float* args, void* userObj);

	void killArea(bs::UserTypeBase* object);

	void setWidth(bs::UserTypeBase* object, float value);

	float getWidth(bs::UserTypeBase* object);

	void setHeight(bs::UserTypeBase* object, float value);

	float getHeight(bs::UserTypeBase* object);

	void setInnerWidth(bs::UserTypeBase* object, float value);

	float getInnerWidth(bs::UserTypeBase* object);

	void setInnerHeight(bs::UserTypeBase* object, float value);

	float getInnerHeight(bs::UserTypeBase* object);

	void setAngle(bs::UserTypeBase* object, float value);

	float getAngle(bs::UserTypeBase* object);

	void setStart(bs::UserTypeBase* object, float value);

	float getStart(bs::UserTypeBase* object);

	void setEnd(bs::UserTypeBase* object, float value);

	float getEnd(bs::UserTypeBase* object);

	void setAlpha(bs::UserTypeBase* object, float value);

	float getAlpha(bs::UserTypeBase* object);
};

// Function hooks
bs::UserTypeBase* area_emitQuadC(float x, float y, const float* args, void* userObj);

bs::UserTypeBase* area_emitQuadB(float x, float y, const float* args, void* userObj);

bs::UserTypeBase* area_emitEllipse(float x, float y, const float* args, void* userObj);

bs::UserTypeBase* area_emitArc(float x, float y, const float* args, void* userObj);

void area_kill(bs::UserTypeBase* object, void* userObj);

void area_setWidth(bs::UserTypeBase* object, float value);

float area_getWidth(bs::UserTypeBase* object);

void area_setHeight(bs::UserTypeBase* object, float value);

float area_getHeight(bs::UserTypeBase* object);

void area_setInnerWidth(bs::UserTypeBase* object, float value);

float area_getInnerWidth(bs::UserTypeBase* object);

void area_setInnerHeight(bs::UserTypeBase* object, float value);

float area_getInnerHeight(bs::UserTypeBase* object);

void area_setAngle(bs::UserTypeBase* object, float value);

float area_getAngle(bs::UserTypeBase* object);

void area_setStart(bs::UserTypeBase* object, float value);

float area_getStart(bs::UserTypeBase* object);

void area_setEnd(bs::UserTypeBase* object, float value);

float area_getEnd(bs::UserTypeBase* object);

void area_setAlpha(bs::UserTypeBase* object, float value);

float area_getAlpha(bs::UserTypeBase* object);


#endif