#ifndef __UNITSYSTEM_H__
#define __UNITSYSTEM_H__

#include <list>
#include "bsBulletScript.h"
#include "RendererGL.h"

struct Bullet;
struct Area;
struct SoundEffect;

struct Unit
{
private:

	float mX, mY;

	bs::Gun* mGun;

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

	// For bulletscript
	bs::FireTypeControl* __ft;
};

class UnitSystem
{
	friend struct Unit;

	static bs::Machine<Bullet, Area, SoundEffect, Unit>* mMachine;

	static std::vector<Unit*> mUnits;
	static std::list<int> mFreeList;	

	static void killUnit(Unit* unit);

public:

	static void initialise(bs::Machine<Bullet, Area, SoundEffect, Unit>* machine);

	static void shutdown();

	static void update(float frameTime);

	// Scripting
	static Unit* emitUnit(bs::bstype x, bs::bstype y, const bs::bstype* args);

	static void killUnit(void* object);

	static void render(RendererGL* renderer);

};

#endif