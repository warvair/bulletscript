#ifndef __SHIP_H__
#define __SHIP_H__

#include <list>
#include "bsGun.h"
#include "RendererGL.h"
#include "BulletSystem.h"
#include "RendererGL.h"
#include "bsBulletGun.h"
#include "bsAreaGun.h"

class Ship
{
protected:

	BS::ScriptMachine* mScriptMachine;
	BS::BulletMachine<Bullet>* mBulletMachine;
	
	float mX;
	float mY;

	float mAngle;

	int mWidth;
	int mHeight;

	GLuint mTexture;

	struct GunInstance
	{
		BS::GunController *gun;
		float xOffset, yOffset;
		bool active;
	};

	typedef std::vector<GunInstance> GunList;
	GunList mGuns;

	void setGun(int index, const BS::String& def);

	virtual void updateGuns(float frameTime) = 0;

	virtual void updateImpl(float frameTime) {}

public:

	Ship (const BS::String& image, float x, float y,
		BS::ScriptMachine* sm, BS::BulletMachine<Bullet>* bm);

	virtual ~Ship();

	float getX() const;

	float getY() const;

	virtual void addGun(const BS::String& def, float x, float y) = 0;

	void move(float x, float y);

	void set(float x, float y);

	void toggleGun(int index);

	void update(float frameTime);

	virtual void render(RendererGL* renderer);

};

class BulletShip : public Ship
{
	void updateGuns(float frameTime);

public:

	BulletShip (const BS::String& image, float x, float y,
		BS::ScriptMachine* sm, BS::BulletMachine<Bullet>* bm) :
		Ship(image, x, y, sm, bm)
	{
	}

	void addGun(const BS::String& def, float x, float y);

	void emitAngleBullet(float x, float y, float angle, float speed, float damage);

	void emitTargetBullet(float x, float y, float speed, float damage);
};

class AreaShip : public Ship
{
	friend class ShipAreaGunController;

	class ShipAreaGunController : public BS::AreaGunController
	{
		AreaShip* mShip;

		void angleToImpl(float value, float time)
		{
			mShip->mAngleTime = time;
			mShip->mAngleSpeed = (value - mShip->mAngle) / time;
		}

	public:

		ShipAreaGunController(BS::ScriptMachine *scriptMachine, AreaShip* ship) :
			BS::AreaGunController(scriptMachine, &(ship->getPoints()), 0, 0, &(ship->getStrength())),
			mShip(ship)
		{
		}
	};

	class AreaGunRenderer
	{
		AreaShip *mShip;

	public:

		AreaGunRenderer(AreaShip *ship) :
			mShip (ship) {}

		void render(BS::AreaGunController* gun, RendererGL* renderer, bool solid);
	};

	AreaGunRenderer* mGunRenderer;

	std::vector<float> mPoints;

	float mStrength;

	float mAngleTime, mAngleSpeed;

	void updateGuns(float frameTime);

	void updateImpl(float frameTime);

public:

	AreaShip (const BS::String& image, float x, float y, BS::ScriptMachine* sm) :
		Ship(image, x, y, sm, 0),
		mStrength(1.0f),
		mAngleTime(0.0f),
		mAngleSpeed(0.0f)
	{
		mGunRenderer = new AreaGunRenderer(this);
	}

	~AreaShip()
	{
		if (mGunRenderer)
			delete mGunRenderer;
	}

	std::vector<float>& getPoints ()
	{
		return mPoints;
	}

	float& getStrength()
	{
		return mStrength;
	}

	void addGun(const BS::String& def, float x, float y);

	void render(RendererGL* renderer);

};

class BombShip : public Ship
{
	friend class ShipAreaGunController;

	class ShipAreaGunController : public BS::AreaGunController
	{
		BombShip* mShip;

	public:

		ShipAreaGunController(BS::ScriptMachine *scriptMachine, BombShip* ship) :
			BS::AreaGunController(scriptMachine, &(ship->getPoints()), 0, 0, &(ship->getStrength())),
			mShip(ship)
		{
		}
	};

	class AreaGunRenderer
	{
		BombShip *mShip;

	public:

		AreaGunRenderer(BombShip *ship) :
			mShip (ship) {}

		void render(BS::AreaGunController* gun, RendererGL* renderer, bool solid);
	};

	AreaGunRenderer* mGunRenderer;

	std::vector<float> mPoints;

	float mStrength;

	void updateGuns(float frameTime);

	void updateImpl(float frameTime);

public:

	BombShip (float x, float y, BS::ScriptMachine* sm) :
		Ship("", x, y, sm, 0),
		mStrength(1.0f)
	{
		mGunRenderer = new AreaGunRenderer (this);
	}

	~BombShip()
	{
		if (mGunRenderer)
			delete mGunRenderer;
	}

	std::vector<float> &getPoints ()
	{
		return mPoints;
	}

	float& getStrength()
	{
		return mStrength;
	}

	void addGun(const BS::String& def, float x, float y);

	void render(RendererGL* renderer);

};
/*
class ArcShip
{
	friend class ShipArcGunController;

	class ShipArcGunController : public BS::ArcGunController
	{
		ArcShip* mShip;

	public:

		ShipArcGunController(BS::ScriptMachine *scriptMachine, ArcShip* ship) :
			BS::ArcGunController(scriptMachine, &(ship->getPoints()), 0, 0, &(ship->getStrength())),
			mShip(ship)
		{
		}
	};

	class AreaGunRenderer
	{
		BombShip *mShip;

	public:

		AreaGunRenderer(BombShip *ship) :
			mShip (ship) {}

		void render(BS::AreaGunController* gun, RendererGL* renderer, bool solid);
	};

	AreaGunRenderer* mGunRenderer;

	std::vector<float> mPoints;

	float mStrength;

	void updateGuns(float frameTime);

	void updateImpl(float frameTime);

public:

	BombShip (float x, float y, BS::ScriptMachine* sm) :
		Ship("", x, y, sm, 0),
		mStrength(1.0f)
	{
		mGunRenderer = new AreaGunRenderer (this);
	}

	~BombShip()
	{
		if (mGunRenderer)
			delete mGunRenderer;
	}

	std::vector<float> &getPoints ()
	{
		return mPoints;
	}

	float& getStrength()
	{
		return mStrength;
	}

	void addGun(const BS::String& def, float x, float y);

	void render(RendererGL* renderer);

};
*/

#endif