#include <cmath>
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
	mY (y),
	mAngle(180.0f)
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
void BulletShip::addGun(const Shmuppet::String& def, float x, float y)
{
	Shmuppet::BulletGunController<Bullet>* gun =
		new Shmuppet::BulletGunController<Bullet>(mScriptMachine, mBulletMachine);
	gun->setDefinition(def);

	GunInstance shipGun;
	shipGun.gun = gun;
	shipGun.active = true;
	shipGun.xOffset = x;
	shipGun.yOffset = y;
	mGuns.push_back(shipGun);
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
			gun.gun->setInstanceVariable(Shmuppet::Instance_Gun_X, mX + gun.xOffset);
			gun.gun->setInstanceVariable(Shmuppet::Instance_Gun_Y, mY + gun.yOffset);
			gun.gun->setInstanceVariable(Shmuppet::Instance_Gun_Angle, mAngle);

			gun.gun->update(frameTime);

			// Run script
			gun.gun->runScript(frameTime);
		}

		++it;
	}
}
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
void AreaShip::AreaGunRenderer::render(Shmuppet::AreaGunController* gun, RendererGL* renderer)
{
	std::vector<float> p = gun->getPoints();
	int numPoints = gun->getNumPoints();

	if (numPoints == 3)
	{
		renderer->renderQuickTriangle(p[0], p[1], p[2], p[3], p[4], p[5], 0);
	}
	else if (numPoints == 4)
	{
		renderer->renderQuickTriangle(p[0], p[1], p[2], p[3], p[4], p[5], 0);
		renderer->renderQuickTriangle(p[4], p[5], p[6], p[7], p[0], p[1], 0);
	}
	else
	{
		for (int i = 0; i < (numPoints - 2) * 2; i += 2)
			renderer->renderQuickTriangle(p[0], p[1], p[i + 2], p[i + 3], p[i + 4], p[i + 5], 0);
	}
}
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
void AreaShip::addGun(const Shmuppet::String& def, float x, float y)
{
	Shmuppet::AreaGunController* gun = new ShipAreaGunController(mScriptMachine);
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
			float pX = -sin(mAngle * Shmuppet::DEG_TO_RAD) * 80;
			float pY = cos(mAngle * Shmuppet::DEG_TO_RAD) * 80;
			float w2 = mWidth / 2;
			float h2 = mHeight / 2;
			gun.gun->setInstanceVariable(Shmuppet::Instance_Gun_X, mX + w2 - 10 + pX);
			gun.gun->setInstanceVariable(Shmuppet::Instance_Gun_Y, mY + h2 - 10 + pY);


			gun.gun->setInstanceVariable(Shmuppet::Instance_Gun_Angle, mAngle);

			gun.gun->update(frameTime);

			// Run script
			gun.gun->runScript(frameTime);
		}

		++it;
	}
}
// --------------------------------------------------------------------------------
void AreaShip::updateImpl(float frameTime)
{
	static int dir = 1;
	mAngle -= 20 * dir * frameTime;
	if (mAngle <= 90)
	{
		mAngle = 90;
		dir *= -1;
	}

	if (mAngle >= 180)
	{
		mAngle = 180;
		dir *= -1;
	}
}
// --------------------------------------------------------------------------------
void AreaShip::render(RendererGL* renderer)
{
	int w2 = mWidth / 2;
	int h2 = mHeight / 2;
	
	// Render moving part
	glPushMatrix();
	glTranslatef(mX + w2 - 10, mY + h2 - 10, 0);
	glRotatef(mAngle, 0, 0, 1);
	glTranslatef(-10, 0, 0);
	renderer->renderQuickUVQuad(0, 0, 20, 80, 0.0f, 1.0f, 0.15625f, 0.375f, mTexture);
	glPopMatrix();

	// Render stationary part
	renderer->renderQuickUVQuad(mX, mY, mX + w2, mY + h2,
		0.5f, 0.5f, 1.0f, 1.0f, mTexture);

	// Render guns
	GunList::iterator it = mGuns.begin();
	while (it != mGuns.end())
	{
		const GunInstance& gun = *it;

		if (gun.active)
		{
			mGunRenderer->render(static_cast<Shmuppet::AreaGunController*>(gun.gun), renderer);
		}

		++it;
	}
}
// --------------------------------------------------------------------------------