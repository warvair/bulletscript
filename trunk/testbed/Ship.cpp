#include <iostream>
#include "Ship.h"

// --------------------------------------------------------------------------------
Ship::Ship(const Shmuppet::String& image, 
		   float x, 
		   float y,
		   Shmuppet::ScriptMachine* sm, 
		   Shmuppet::BulletMachine<Bullet>* bm) :
	mScriptMachine (sm),
	mBulletMachine (bm),
	mX (x),
	mY (y)
{
	TGALoader loader(image);
	mTexture = loader.loadToVRAM(mWidth, mHeight);
}
// --------------------------------------------------------------------------------
Ship::~Ship()
{
	GunList::iterator it = mGuns.begin();
	while (it != mGuns.end())
	{
		delete (*it).gun;
		++it;
	}
}
// --------------------------------------------------------------------------------
void Ship::addGun(const Shmuppet::String& def, 
				  float x, 
				  float y)
{
	// Create GunInstance from GunDefinition
	Shmuppet::Gun<Bullet> *gun = new Shmuppet::Gun<Bullet>(mScriptMachine, mBulletMachine);

	Shmuppet::GunDefinition* gunDef = mBulletMachine->getGunDefinition(def);
	if (!gunDef)
	{
		delete gun;
		return;
	}

	gun->setDefinition(gunDef);

	GunInstance shipGun;
	shipGun.gun = gun;
	shipGun.active = true;
	shipGun.xOffset = x;
	shipGun.yOffset = y;
	mGuns.push_back (shipGun);
}
// --------------------------------------------------------------------------------
float Ship::getX() const
{
	return mX;
}
// --------------------------------------------------------------------------------
float Ship::getY() const
{
	return mY;
}
// --------------------------------------------------------------------------------
void Ship::move (float x, float y)
{
	mX += x;
	mY += y;
}
// --------------------------------------------------------------------------------
void Ship::toggleGun(int index)
{
	mGuns[index].active = !mGuns[index].active;
}
// --------------------------------------------------------------------------------
void Ship::updateGuns(float frameTime)
{
	GunList::iterator it = mGuns.begin();
	while (it != mGuns.end())
	{
		const GunInstance& gun = *it;

		if (gun.active)
		{
			gun.gun->setInstanceVariable(Shmuppet::Instance_Gun_X, mX + gun.xOffset);
			gun.gun->setInstanceVariable(Shmuppet::Instance_Gun_Y, mY + gun.yOffset);
			gun.gun->updateBulletAffectors();

			// Run script
			gun.gun->runScript(frameTime);
		}

		++it;
	}
}
// --------------------------------------------------------------------------------
void Ship::render(RendererGL* renderer)
{
	int w2 = mWidth / 2;
	int h2 = mHeight / 2;
	renderer->renderQuickQuad(mX - w2, mY - h2, mX + w2, mY + h2, mTexture);
}
// --------------------------------------------------------------------------------
