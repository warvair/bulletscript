#ifndef __AREASYSTEM_H__
#define __AREASYSTEM_H__

#include "bsBulletScript.h"
#include "RendererGL.h"

struct Bullet;
struct SoundEffect;
struct Unit;

// Areas are either quads or circles.
enum AreaType
{
	AT_QuadCentred,
	AT_QuadBased,
	AT_Ellipse,
	AT_Arc
};

struct Area
{
	int type;			// quad or ellipse
	bs::bstype x, y;	// centre
	bs::bstype w, h;	// width, height.  Also used for ellipse
	bs::bstype angle;
	bs::bstype start, end; // generic, can be used for arcs
	bs::bstype innerw, innerh;
	bs::bstype fade;

	// Internal variables, do not modify in affector function!
	int __index;
	float __time;

	// For bulletscript
	bs::FireTypeControl* __ft;

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

	static bs::Machine<Bullet, Area, SoundEffect, Unit>* mMachine;

	static const int BATTERY_SIZE = 128;

	static std::vector<Area> mAreas;
	static std::vector<unsigned int> mFreeList[2];
	static int mStoreIndex;
	static int mUseIndex;

	static std::vector<Area> mSpawnedAreas;

	static unsigned int getFreeAreaSlot();

	static void killArea(Area* a);
	
public:

	static void initialise(bs::Machine<Bullet, Area, SoundEffect, Unit>* machine);

	static int update(float frameTime);

	static void render(RendererGL* renderer);

	// Scripting
	static Area* emitQuadC(bs::bstype x, bs::bstype y, const bs::bstype* args);

	static Area* emitQuadB(bs::bstype x, bs::bstype y, const bs::bstype* args);

	static Area* emitEllipse(bs::bstype x, bs::bstype y, const bs::bstype* args);

	static Area* emitArc(bs::bstype x, bs::bstype y, const bs::bstype* args);

	static void killArea(void* object);

	static void setWidth(void* object, bs::bstype value);

	static bs::bstype getWidth(void* object);

	static void setHeight(void* object, bs::bstype value);

	static bs::bstype getHeight(void* object);

	static void setInnerWidth(void* object, bs::bstype value);

	static bs::bstype getInnerWidth(void* object);

	static void setInnerHeight(void* object, bs::bstype value);

	static bs::bstype getInnerHeight(void* object);

	static void setAngle(void* object, bs::bstype value);

	static bs::bstype getAngle(void* object);

	static void setStart(void* object, bs::bstype value);

	static bs::bstype getStart(void* object);

	static void setEnd(void* object, bs::bstype value);

	static bs::bstype getEnd(void* object);

	static void setFade(void* object, bs::bstype value);

	static bs::bstype getFade(void* object);
};

#endif