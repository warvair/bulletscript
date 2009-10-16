#include <iostream>
#include <cmath>
#include "Ship.h"

// --------------------------------------------------------------------------------
Ship::Ship(const BS::String& image, 
		   float x, 
		   float y,
		   BS::ScriptMachine* sm, 
		   BS::BulletMachine<Bullet>* bm) :
	mScriptMachine (sm),
	mBulletMachine (bm),
	mX (x),
	mY (y),
	mAngle(180.0f)
{
	if (image != "")
	{
		TGALoader loader(image);
		mTexture = loader.loadToVRAM(mWidth, mHeight);
	}
	else
	{
		mTexture = 0;
		mWidth = 0;
		mHeight = 0;
	}
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
void Ship::move(float x, float y)
{
	mX += x;
	mY += y;
}
// --------------------------------------------------------------------------------
void Ship::set(float x, float y)
{
	mX = x;
	mY = y;
}
// --------------------------------------------------------------------------------
void Ship::toggleGun(int index)
{
	mGuns[index].active = !mGuns[index].active;
}
// --------------------------------------------------------------------------------
void Ship::update(float frameTime)
{
	updateImpl(frameTime);
	updateGuns(frameTime);
}
// --------------------------------------------------------------------------------
void Ship::render(RendererGL* renderer)
{
	int w2 = mWidth / 2;
	int h2 = mHeight / 2;
	renderer->renderQuickQuad(mX - w2, mY - h2, mX + w2, mY + h2, mTexture);
}
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
void BulletShip::addGun(const BS::String& def, float x, float y)
{
	BS::BulletGunController<Bullet>* gun =
		new BS::BulletGunController<Bullet>(mScriptMachine, mBulletMachine, this);
	gun->setDefinition(def);

	GunInstance shipGun;
	shipGun.gun = gun;
	shipGun.active = true;
	shipGun.xOffset = x;
	shipGun.yOffset = y;
	mGuns.push_back(shipGun);
}
// --------------------------------------------------------------------------------
void BulletShip::emitAngleBullet(float x, float y, float angle, float speed, float damage)
{
}
// --------------------------------------------------------------------------------
void BulletShip::emitTargetBullet(float x, float y, float speed, float damage)
{
}
// --------------------------------------------------------------------------------
void BulletShip::updateGuns(float frameTime)
{
	GunList::iterator it = mGuns.begin();
	while (it != mGuns.end())
	{
		const GunInstance& gun = *it;

		if (gun.active)
		{
			// If you want the gun to rotate around a point, so that the emission position
			// and angle change, calculate the position/angle and expose them to the script
			// here.  Then use Gun_Angle as emission angle in script.
			gun.gun->update(frameTime, mX + gun.xOffset, mY + gun.yOffset, mAngle);

			// Run script
			gun.gun->runScript(frameTime);
		}

		++it;
	}
}
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
void AreaShip::AreaGunRenderer::render(BS::AreaGunController* gun, 
									   RendererGL* renderer,
									   bool solid)
{
	std::vector<float> p = mShip->getPoints();
	float strength = mShip->getStrength();
	int numPoints = (int) p.size() / 2;

	if (numPoints == 3)
	{
		renderer->renderQuickTriangle(p[0], p[1], p[2], p[3], p[4], p[5], strength, 0);
	}
	else if (numPoints == 4)
	{
		renderer->renderQuickTriangle(p[0], p[1], p[2], p[3], p[4], p[5], strength, 0);
		renderer->renderQuickTriangle(p[4], p[5], p[6], p[7], p[0], p[1], strength, 0);
	}
	else
	{
		for (int i = 0; i < (numPoints - 2) * 2; i += 2)
			renderer->renderQuickTriangle(p[0], p[1], p[i + 2], p[i + 3], p[i + 4], p[i + 5], strength, 0);
	}
}
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
void AreaShip::addGun(const BS::String& def, float x, float y)
{
	BS::AreaGunController* gun = new ShipAreaGunController(mScriptMachine, this);
	gun->setDefinition(def);

	GunInstance shipGun;
	shipGun.gun = gun;
	shipGun.active = true;
	shipGun.xOffset = x;
	shipGun.yOffset = y;
	mGuns.push_back(shipGun);
}
// --------------------------------------------------------------------------------
void AreaShip::updateGuns(float frameTime)
{
	GunList::iterator it = mGuns.begin();
	while (it != mGuns.end())
	{
		const GunInstance& gun = *it;

		if (gun.active)
		{
			// mX + w2 - 10, mY + h2 - 10
			float pX = -sin(mAngle * BS::DEG_TO_RAD) * 80;
			float pY = cos(mAngle * BS::DEG_TO_RAD) * 80;
			float w2 = mWidth / 2;
			float h2 = mHeight / 2;

			gun.gun->update(frameTime, mX + w2 - 10 + pX, mY + h2 - 10 + pY, mAngle);

			// Run script
			gun.gun->runScript(frameTime);
		}

		++it;
	}
}
// --------------------------------------------------------------------------------
void AreaShip::updateImpl(float frameTime)
{
	// To control the beam from script, set it in script, and update it in code
	// like this:
	if (mAngleTime >= 0)
	{
		mAngle += mAngleSpeed * frameTime;
		mAngleTime -= frameTime;
	}

	// To control the beam from code, do not set the angle from script, and update
	// it manually, like this:
/*
	static int s_dir = -1;
	mAngle += 20 * frameTime * s_dir;
	if (mAngle <= 90)
	{
		s_dir *= -1;
	}
	if (mAngle >= 180)
	{
		s_dir *= -1;
	}
*/
}
// --------------------------------------------------------------------------------
void AreaShip::render(RendererGL* renderer)
{
	int w2 = mWidth / 2;
	int h2 = mHeight / 2;

	// Render guns
	GunList::iterator it = mGuns.begin();
	while (it != mGuns.end())
	{
		const GunInstance& gun = *it;

		if (gun.active)
		{
			mGunRenderer->render(static_cast<BS::AreaGunController*>(gun.gun), renderer, true);
		}

		++it;
	}

	// Render moving part - all numbers here are hardcoded for turret.tga
	glPushMatrix();
	glTranslatef(mX + w2 - 10, mY + h2 - 10, 0);
	glRotatef(mAngle, 0, 0, 1);
	glTranslatef(-10, 0, 0);
	renderer->renderQuickUVQuad(0, 0, 20, 80, 0.0f, 1.0f, 0.15625f, 0.375f, mTexture);
	glPopMatrix();

	// Render stationary part
	renderer->renderQuickUVQuad(mX, mY, mX + w2, mY + h2,
		0.5f, 0.5f, 1.0f, 1.0f, mTexture);
}
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
void BombShip::AreaGunRenderer::render(BS::AreaGunController* gun, 
									   RendererGL* renderer,
									   bool solid)
{
	std::vector<float> p = mShip->getPoints();
	float strength = mShip->getStrength();
	int numPoints = (int) p.size() / 2;

	if (numPoints == 3)
	{
		if (solid)
		{
			renderer->renderQuickTriangle(p[0], p[1], p[2], p[3], p[4], p[5], strength, 0);
		}
		else
		{

		}
	}
	else if (numPoints == 4)
	{
		if (solid)
		{
			renderer->renderQuickTriangle(p[0], p[1], p[2], p[3], p[4], p[5], strength, 0);
			renderer->renderQuickTriangle(p[4], p[5], p[6], p[7], p[0], p[1], strength, 0);
		}
		else
		{
		}
	}
	else
	{
		if (solid)
		{
			for (int i = 0; i < (numPoints - 2) * 2; i += 2)
				renderer->renderQuickTriangle(p[0], p[1], p[i + 2], p[i + 3], p[i + 4], p[i + 5], strength, 0);
		}
		else
		{
			renderer->renderQuickLines(p, numPoints, strength);
		}
	}
}
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
void BombShip::addGun(const BS::String& def, float x, float y)
{
	BS::AreaGunController* gun = new ShipAreaGunController(mScriptMachine, this);
	gun->setDefinition(def);

	GunInstance shipGun;
	shipGun.gun = gun;
	shipGun.active = true;
	shipGun.xOffset = x;
	shipGun.yOffset = y;
	mGuns.push_back(shipGun);
}
// --------------------------------------------------------------------------------
void BombShip::updateGuns(float frameTime)
{
	GunList::iterator it = mGuns.begin();
	while (it != mGuns.end())
	{
		const GunInstance& gun = *it;

		if (gun.active)
		{
			gun.gun->update(frameTime, mX, mY, mAngle);

			// Run script
			gun.gun->runScript(frameTime);
		}

		++it;
	}
}
// --------------------------------------------------------------------------------
void BombShip::updateImpl(float frameTime)
{
}
// --------------------------------------------------------------------------------
void BombShip::render(RendererGL* renderer)
{
	// Render guns
	GunList::iterator it = mGuns.begin();
	while (it != mGuns.end())
	{
		const GunInstance& gun = *it;

		if (gun.active)
		{
			mGunRenderer->render(static_cast<BS::AreaGunController*>(gun.gun), renderer, false);
		}

		++it;
	}
}
// --------------------------------------------------------------------------------