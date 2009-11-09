#ifndef __UNITSYSTEM_H__
#define __UNITSYSTEM_H__

#include <list>
#include "bsBulletScript.h"
#include "RendererGL.h"

struct Unit : public bs::UserTypeBase
{
private:

	float mX, mY;

	bs::Emitter* mGun;

public:

	Unit();

	void setPosition(float x, float y);

	void setGun(const bs::String& gun);

	bool update(float frameTime);

	void render(RendererGL* renderer);

	// internal
	bool __active;
	int __index;

	void __deactivate();
};

class UnitSystem
{
	friend struct Unit;

	static bs::Machine* mMachine;

	static std::vector<Unit*> mUnits;
	static std::list<int> mFreeList;	

	static void killUnit(Unit* unit);

public:

	static void initialise(bs::Machine* machine);

	static void shutdown();

	static void update(float frameTime);

	// Scripting
	static bs::UserTypeBase* emitUnit(bs::bstype x, bs::bstype y, const bs::bstype* args);

	static void killUnit(bs::UserTypeBase* object);

	static void render(RendererGL* renderer);

};

#endif