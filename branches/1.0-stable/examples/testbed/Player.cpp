#include "Player.h"
#include "RendererGL.h"
#include "Platform.h"

extern BulletBattery* g_playerBullets;

Player::Player(bs::Machine* machine) :
	mTexture(0),
	mWidth(0),
	mHeight(0),
	mX(SCREEN_WIDTH / 2),
	mY(100),
	mGunController(0),
	mMachine(machine)
{
	setGuns("PlayerController");
}

Player::~Player()
{
	if (mGunController)
		mMachine->destroyController(mGunController);
}

void Player::setImage(const char* file)
{
	TGALoader img(file);
	mTexture = img.loadToVRAM (mWidth, mHeight);
}

void Player::setGuns(const char* guns)
{
	mGunController = mMachine->createController(guns, g_playerBullets);
	mGunController->setX(mX);
	mGunController->setY(mY);
	mGunController->setAngle(0.0f);
	
	enableGuns(false);
}

void Player::enableGuns(bool enable)
{
	mGunController->enable(enable);
}

void Player::setPosition(float x, float y)
{
	mX = x;
	mY = y;

	if (mGunController)
	{
		mGunController->setX(mX);
		mGunController->setY(mY);
	}
}

float Player::getX() const
{
	return mX;
}

float Player::getY() const
{
	return mY;
}

void Player::doInput(float frameTime)
{
	if (keyDown(SDLK_LEFT))
	{
		float x = getX();
		float y = getY();

		x -= 192 * frameTime;
		if (x < 64)
			x = 64;

		setPosition(x, y);
	}
	if (keyDown(SDLK_RIGHT))
	{
		float x = getX();
		float y = getY();

		x += 192 * frameTime;
		if (x > (SCREEN_WIDTH - 64))
			x = SCREEN_WIDTH - 64;

		setPosition(x, y);
	}
	if (keyDown(SDLK_DOWN))
	{
		float x = getX();
		float y = getY();

		y -= 192 * frameTime;
		if (y < 64)
			y = 64;

		setPosition(x, y);
	}
	if (keyDown(SDLK_UP))
	{
		float x = getX();
		float y = getY();

		y += 192 * frameTime;
		if (y > (SCREEN_HEIGHT - 64))
			y = SCREEN_HEIGHT - 64;

		setPosition(x, y);
	}
	if (keyPressed(SDLK_z))
	{
		enableGuns(true);
	}
	else if (keyReleased(SDLK_z))
	{
		enableGuns(false);
	}
}

void Player::render()
{
	int w2 = mWidth / 2;
	int h2 = mHeight / 2;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(mX, mY, 0);
	
	glBindTexture(GL_TEXTURE_2D, mTexture);
	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	{
			glTexCoord2i(0, 0);
			glVertex2i(-w2, -h2);
			glTexCoord2i(1, 0);
			glVertex2i(w2, -h2);
			glTexCoord2i(1, 1);
			glVertex2i(w2, h2);
			glTexCoord2i(0, 1);
			glVertex2i(-w2, h2);
	}
	glEnd();

	glPopMatrix();
}
