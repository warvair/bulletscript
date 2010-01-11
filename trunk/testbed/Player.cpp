#include "Player.h"
#include "RendererGL.h"

Player::Player(bs::Machine* machine) :
	mTexture(0),
	mWidth(0),
	mHeight(0),
	mX(SCREEN_WIDTH / 2),
	mY(100),
	mGunController(0),
	mMachine(machine)
{
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
	mGunController = mMachine->createController(guns);
	mGunController->setX(mX);
	mGunController->setY(mY);
	mGunController->setAngle(0.0f);
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
			glVertex2f(-w2, -h2);
			glTexCoord2i(1, 0);
			glVertex2f(w2, -h2);
			glTexCoord2i(1, 1);
			glVertex2f(w2, h2);
			glTexCoord2i(0, 1);
			glVertex2f(-w2, h2);
	}
	glEnd();

	glPopMatrix();
}
