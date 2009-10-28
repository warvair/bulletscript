#ifndef __AREASYSTEM_H__
#define __AREASYSTEM_H__

#include "bsBulletScript.h"
#include "RendererGL.h"

struct Bullet;

// Areas are either quads or circles.
enum AreaType
{
	AT_QuadCentred,
	AT_QuadBased,
	AT_Ellipse
};

struct Area
{
	int type;			// quad or ellipse
	BS::bstype x, y;	// centre
	BS::bstype w, h;	// width, height.  Also used for ellipse
	BS::bstype angle;
	BS::bstype fade;

	// Internal variables, do not modify in affector function!
	int __index;
	float __time;

	// For bulletscript
	BS::FireTypeScriptRecord* __ft;

	bool __active;
	char padding[7]; // pad to 48 bytes

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

	static BS::Machine<Bullet, Area>* mMachine;

	static const int BATTERY_SIZE = 128;

	static std::vector<Area> mAreas;
	static std::vector<unsigned int> mFreeList[2];
	static int mStoreIndex;
	static int mUseIndex;

	static std::vector<Area> mSpawnedAreas;

	static unsigned int getFreeAreaSlot();

	static void killArea(Area* a);
	
public:

	static void initialise(BS::Machine<Bullet, Area>* machine);

	static int update(float frameTime);

	static void render(RendererGL* renderer);

	// Scripting
	static Area* emitQuadC(BS::bstype x, BS::bstype y, const BS::bstype* args);

	static Area* emitQuadB(BS::bstype x, BS::bstype y, const BS::bstype* args);

	static Area* emitEllipse(BS::bstype x, BS::bstype y, const BS::bstype* args);

	static void killArea(void* object);

	static void setWidth(void* object, BS::bstype value);

	static BS::bstype getWidth(void* object);

	static void setHeight(void* object, BS::bstype value);

	static BS::bstype getHeight(void* object);

	static void setAngle(void* object, BS::bstype value);

	static BS::bstype getAngle(void* object);

	static void setFade(void* object, BS::bstype value);

	static BS::bstype getFade(void* object);
};

#endif