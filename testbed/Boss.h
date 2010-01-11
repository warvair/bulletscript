#ifndef __BOSS_H__
#define __BOSS_H__

#include "bsBulletScript.h"

class Boss
{
	unsigned int mTexture;
	
	int mWidth, mHeight;
	
	float mX, mY, mAngle;
	
	int mHealth;

	bs::Controller* mGunController;

	bs::Machine* mMachine;

public:

	explicit Boss(bs::Machine* machine);

	~Boss();

	void setImage(const char* file);

	void setGuns(const char* guns);

	void setPosition(float x, float y);

	void setAngle(float angle);

	float getX() const;

	float getY() const;

	int getHeight() const;

	bool damage(int damage);

	int getHealth() const;

	void startGuns();

	void render();
};

class BossManager
{
	static const int NUM_BOSSES = 1;
	
	Boss* mBosses[NUM_BOSSES];
	
	int mCurBoss;

	enum State
	{
		State_MoveOnScreen,
		State_StartGuns,
		State_Update,
		State_Intermission
	};

	int mCurState;

public:

	BossManager(bs::Machine* machine);

	~BossManager();

	void loadImages();

	void update(float frameTime);

	void render();
};

#endif