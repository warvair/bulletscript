#include "UnitSystem.h"

bs::Machine<Bullet, Area, SoundEffect, Unit>* UnitSystem::mMachine = 0;
std::vector<Unit*> UnitSystem::mUnits;
std::list<int> UnitSystem::mFreeList;

// --------------------------------------------------------------------------------
Unit::Unit() :
	mX(0),
	mY(0),
	mGun(0),
	__active(false),
	__index(-1)
{
}
// --------------------------------------------------------------------------------
void Unit::setPosition(float x, float y)
{
	mX = x;
	mY = y;
//	mGun->setX(x);
//	mGun->setY(y);
}
// --------------------------------------------------------------------------------
void Unit::setGun(const bs::String& gun)
{
/*
	if (mGun)
		UnitSystem::mMachine->destroyGun(mGun);

	mGun = UnitSystem::mMachine->createGun(gun);
	mGun->setX(mX);
	mGun->setY(mY);
*/
}
// --------------------------------------------------------------------------------
bool Unit::update(float frameTime)
{
	mY -= 60 * frameTime;

	if (mY < -32)
	{
		UnitSystem::killUnit(this);
		return false;
	}
	else
	{
		// update guns
//		mGun->setX(mX);
//		mGun->setY(mY - 16);

		return true;
	}
}
// --------------------------------------------------------------------------------
void Unit::render(RendererGL* renderer)
{
	renderer->renderUnit(mX, mY);
}
// --------------------------------------------------------------------------------
void Unit::__deactivate()
{
	if (mGun)
	{
		UnitSystem::mMachine->destroyGun(mGun);
		mGun = 0;
	}

	__active = false;
}
// --------------------------------------------------------------------------------

// UnitSystem
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
void UnitSystem::initialise(bs::Machine<Bullet, Area, SoundEffect, Unit>* machine)
{
	mMachine = machine;

	mUnits.resize(128);
	for (int i = 0; i < 128; ++i)
	{
		mUnits[i] = new Unit;
		mFreeList.push_back(i);
	}
}
// --------------------------------------------------------------------------------
void UnitSystem::shutdown()
{
	for (int i = 0; i < mUnits.size(); ++i)
		delete mUnits[i];
}
// --------------------------------------------------------------------------------
void UnitSystem::update(float frameTime)
{
	for (int i = 0; i < mUnits.size(); ++i)
		if (mUnits[i]->__active)
			mUnits[i]->update(frameTime);
}
// --------------------------------------------------------------------------------
Unit* UnitSystem::emitUnit(bs::bstype x, bs::bstype y, const bs::bstype* args)
{
	if (mFreeList.empty())
	{
		int curSize = (int) mUnits.size();
		int newSize = curSize * 2;
		for (int i = curSize; i < newSize; ++i)
		{
			mUnits[i] = new Unit;
			mFreeList.push_back(i);
		}
		mUnits.resize(newSize);
	}

	int slot = mFreeList.front();
	mFreeList.pop_front();

	mUnits[slot]->__active = true;
	mUnits[slot]->__index = slot;
	mUnits[slot]->setPosition(x, y);
	mUnits[slot]->setGun("Blaster");

	return mUnits[slot];
}
// --------------------------------------------------------------------------------
void UnitSystem::killUnit(void* object)
{
	Unit* unit = static_cast<Unit*>(object);
	killUnit(unit);
}
// --------------------------------------------------------------------------------
void UnitSystem::killUnit(Unit* unit)
{
	unit->__deactivate();
	mFreeList.push_back(unit->__index);
}
// --------------------------------------------------------------------------------
void UnitSystem::render(RendererGL* renderer)
{
	for (int i = 0; i < mUnits.size(); ++i)
		if (mUnits[i]->__active)
			mUnits[i]->render(renderer);
}
// --------------------------------------------------------------------------------