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
	bs::bstype x, y;	// centre
	bs::bstype w, h;	// width, height.  Also used for ellipse
	bs::bstype angle;
	bs::bstype start, end; // generic, can be used for arcs
	bs::bstype innerw, innerh;
	bs::bstype alpha;

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

	static bs::Machine* mMachine;

	static const int BATTERY_SIZE = 128;

	static std::vector<Area> mAreas;
	static std::vector<unsigned int> mFreeList[2];
	static int mStoreIndex;
	static int mUseIndex;

	static std::vector<Area> mSpawnedAreas;

	static unsigned int getFreeAreaSlot();

	static void killArea(Area* a);
	
public:

	static void initialise(bs::Machine* machine);

	static int update(float frameTime);

	static void render(RendererGL* renderer);

	// Scripting
	static bs::UserTypeBase* emitQuadC(bs::bstype x, bs::bstype y, const bs::bstype* args);

	static bs::UserTypeBase* emitQuadB(bs::bstype x, bs::bstype y, const bs::bstype* args);

	static bs::UserTypeBase* emitEllipse(bs::bstype x, bs::bstype y, const bs::bstype* args);

	static bs::UserTypeBase* emitArc(bs::bstype x, bs::bstype y, const bs::bstype* args);

	static void killArea(bs::UserTypeBase* object);

	static void setWidth(bs::UserTypeBase* object, bs::bstype value);

	static bs::bstype getWidth(bs::UserTypeBase* object);

	static void setHeight(bs::UserTypeBase* object, bs::bstype value);

	static bs::bstype getHeight(bs::UserTypeBase* object);

	static void setInnerWidth(bs::UserTypeBase* object, bs::bstype value);

	static bs::bstype getInnerWidth(bs::UserTypeBase* object);

	static void setInnerHeight(bs::UserTypeBase* object, bs::bstype value);

	static bs::bstype getInnerHeight(bs::UserTypeBase* object);

	static void setAngle(bs::UserTypeBase* object, bs::bstype value);

	static bs::bstype getAngle(bs::UserTypeBase* object);

	static void setStart(bs::UserTypeBase* object, bs::bstype value);

	static bs::bstype getStart(bs::UserTypeBase* object);

	static void setEnd(bs::UserTypeBase* object, bs::bstype value);

	static bs::bstype getEnd(bs::UserTypeBase* object);

	static void setFade(bs::UserTypeBase* object, bs::bstype value);

	static bs::bstype getFade(bs::UserTypeBase* object);
};

#endif