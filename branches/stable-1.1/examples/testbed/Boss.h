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

	bs::Machine* mMachine;

	bool mVisible;

protected:

	bs::Controller* mGunController;

	std::string mImageFile;

	std::string mControllerName;

public:

	explicit Boss(bs::Machine* machine);

	virtual ~Boss();

	void reset();

	void setVisible(bool vis);

	void loadImage();

	void setBounds(int x0, int y0, int x1, int y1);

	void setGuns(const char* guns);

	virtual int getTargetY() const;

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

	virtual void update(float frameTime) = 0;

	void render();
};

class BossManager
{
	static const int NUM_BOSSES = 4;
	
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