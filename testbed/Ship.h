#ifndef __SHIP_H__
#define __SHIP_H__

#include <list>
#include "shGun.h"
#include "RendererGL.h"
#include "BulletSystem.h"

class Ship
{
	Shmuppet::ScriptMachine* mScriptMachine;
	Shmuppet::BulletMachine<Bullet>* mBulletMachine;
	
	float mX;
	float mY;

	int mWidth;
	int mHeight;

	GLuint mTexture;

	struct GunInstance
	{
		Shmuppet::Gun<Bullet> *gun;
		float xOffset, yOffset;
		bool active;
	};

	typedef std::vector<GunInstance> GunList;
	GunList mGuns;

	void setGun(int index, const Shmuppet::String& def);

public:

	Ship (const Shmuppet::String& image, float x, float y,
		Shmuppet::ScriptMachine* sm, Shmuppet::BulletMachine<Bullet>* bm);

	~Ship();

	void addGun(const Shmuppet::String& def, float x, float y);

	float getX() const;

	float getY() const;

	void move (float x, float y);

	void toggleGun(int index);

	void updateGuns(float frameTime);

	void render(RendererGL* renderer);

};

#endif