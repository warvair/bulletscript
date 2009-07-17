#ifndef __SHIP_H__
#define __SHIP_H__

#include <list>
#include "shGun.h"
#include "RendererGL.h"
#include "BulletSystem.h"
#include "RendererGL.h"
#include "shBulletGun.h"
#include "shAreaGun.h"

class Ship
{
protected:

	Shmuppet::ScriptMachine* mScriptMachine;
	Shmuppet::BulletMachine<Bullet>* mBulletMachine;
	
	float mX;
	float mY;

	float mAngle;

	int mWidth;
	int mHeight;

	GLuint mTexture;

	struct GunInstance
	{
		Shmuppet::GunController *gun;
		float xOffset, yOffset;
		bool active;
	};

	typedef std::vector<GunInstance> GunList;
	GunList mGuns;

	void setGun(int index, const Shmuppet::String& def);

	virtual void updateGuns(float frameTime) = 0;

	virtual void updateImpl(float frameTime) {}

public:

	Ship (const Shmuppet::String& image, float x, float y,
		Shmuppet::ScriptMachine* sm, Shmuppet::BulletMachine<Bullet>* bm);

	virtual ~Ship();

	float getX() const;

	float getY() const;

	virtual void addGun(const Shmuppet::String& def, float x, float y) = 0;

	void move (float x, float y);

	void toggleGun(int index);

	void update(float frameTime);

	virtual void render(RendererGL* renderer);

};

class BulletShip : public Ship
{
	void updateGuns(float frameTime);

public:

	BulletShip (const Shmuppet::String& image, float x, float y,
		Shmuppet::ScriptMachine* sm, Shmuppet::BulletMachine<Bullet>* bm) :
		Ship(image, x, y, sm, bm)
	{
	}

	void addGun(const Shmuppet::String& def, float x, float y);

};

class AreaShip : public Ship
{
	class ShipAreaGunController : public Shmuppet::AreaGunController
	{
		void strengthToImpl(float value, float time)
		{
			// Change visual
		}

	public:

		ShipAreaGunController(Shmuppet::ScriptMachine *scriptMachine) :
			Shmuppet::AreaGunController(scriptMachine)
		{
		}
	};

	class AreaGunRenderer
	{
	public:

		AreaGunRenderer()
		{
		}

		void render(Shmuppet::AreaGunController* gun, RendererGL* renderer);
	};

	AreaGunRenderer* mGunRenderer;

	void updateGuns(float frameTime);

	void updateImpl(float frameTime);

public:

	AreaShip (const Shmuppet::String& image, float x, float y,
		Shmuppet::ScriptMachine* sm, Shmuppet::BulletMachine<Bullet>* bm) :
		Ship(image, x, y, sm, bm)
	{
		mGunRenderer = new AreaGunRenderer;
	}

	~AreaShip()
	{
		if (mGunRenderer)
			delete mGunRenderer;
	}

	void addGun(const Shmuppet::String& def, float x, float y);

	void render(RendererGL* renderer);

};

#endif