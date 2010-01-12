#ifndef __BOSS_H__
#define __BOSS_H__

#include "bsBulletScript.h"
#include "BulletSystem.h"

class Boss
{
	unsigned int mTexture;
	
	int mWidth, mHeight;

	int mBoundsX0, mBoundsY0, mBoundsX1, mBoundsY1;
	
	float mX, mY, mAngle;
	
	int mHealth;

	bs::Controller* mGunController;

	bs::Machine* mMachine;

	bool mVisible;

public:

	explicit Boss(bs::Machine* machine);

	~Boss();

	void reset();

	void setVisible(bool vis);

	void setImage(const char* file);

	void setBounds(int x0, int y0, int x1, int y1);

	void setGuns(const char* guns);

	void setPosition(float x, float y);

	void setAngle(float angle);

	float getX() const;

	float getY() const;

	int getHeight() const;

	bool damage(int damage);

	void setHealth(int health);

	int getHealth() const;

	void startGuns();

	void stopGuns();

	bool checkCollisions(BulletBattery* bs);

	void render();
};

class BossManager
{
	static const int NUM_BOSSES = 2;
	
	Boss* mBosses[NUM_BOSSES];
	
	int mCurBoss;

	enum State
	{
		State_Setup,
		State_MoveOnScreen,
		State_StartGuns,
		State_Update,
		State_Intermission
	};

	int mCurState;

	float mIdle;

public:

	BossManager(bs::Machine* machine);

	~BossManager();

	void loadImages();

	void update(float frameTime);

	void checkCollisions(BulletBattery* bs);

	void render();
};

#endif