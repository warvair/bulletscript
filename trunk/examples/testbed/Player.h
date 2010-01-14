#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "bsBulletScript.h"

class Player
{
	unsigned int mTexture;

	int mWidth, mHeight;
	
	float mX, mY;
	
	bs::Controller* mGunController;

	bs::Machine* mMachine;

public:

	explicit Player(bs::Machine* machine);

	~Player();

	void setImage(const char* file);

	void setGuns(const char* guns);

	void enableGuns(bool enable);

	void setPosition(float x, float y);

	float getX() const;

	float getY() const;

	void doInput(float frameTime);

	void render();
};

#endif