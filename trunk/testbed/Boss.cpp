#include "Boss.h"
#include "RendererGL.h"

Boss::Boss(bs::Machine* machine) :
	mTexture(0),
	mWidth(0),
	mHeight(0),
	mX(0),
	mY(0),
	mAngle(0),
	mHealth(100),
	mGunController(0),
	mMachine(machine)
{
}

Boss::~Boss()
{
	if (mGunController)
		mMachine->destroyController(mGunController);
}

void Boss::setImage(const char* file)
{
	TGALoader img(file);
	mTexture = img.loadToVRAM (mWidth, mHeight);
}

void Boss::setGuns(const char* guns)
{
	mGunController = mMachine->createController(guns);
	mGunController->setX(mX);
	mGunController->setY(mY);
	mGunController->setAngle(mAngle);
}

void Boss::setPosition(float x, float y)
{
	mX = x;
	mY = y;

	if (mGunController)
	{
		mGunController->setX(mX);
		mGunController->setY(mY);
	}
}

void Boss::setAngle(float angle)
{
	mAngle = angle;

	if (mGunController)
	{
		mGunController->setAngle(mAngle);
	}
}

float Boss::getX() const
{
	return mX;
}

float Boss::getY() const
{
	return mY;
}

int Boss::getHeight() const
{
	return mHeight;
}

bool Boss::damage(int damage)
{
	mHealth -= damage;
	return (mHealth > 0);
}

int Boss::getHealth() const
{
	return mHealth;
}

void Boss::startGuns()
{
	setGuns("Boss1");
}

void Boss::render()
{
	int w2 = mWidth / 2;
	int h2 = mHeight / 2;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(mX, mY, 0);
	glRotatef(mAngle, 0, 0, 1);
	
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




BossManager::BossManager(bs::Machine* machine) :
	mCurBoss(0),
	mCurState(State_MoveOnScreen)
{
	for (int i = 0; i < NUM_BOSSES; ++i)
	{
		mBosses[i] = new Boss(machine);
		mBosses[i]->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT + 100);
		mBosses[i]->setAngle(0);
	}
}

BossManager::~BossManager()
{
	for (int i = 0; i < NUM_BOSSES; ++i)
	{
		delete mBosses[i];
	}
}

void BossManager::loadImages()
{
	mBosses[0]->setImage("boss1.tga");
}

void BossManager::update(float frameTime)
{
	switch(mCurState)
	{
	case State_MoveOnScreen:
		{
			int yTarget = SCREEN_HEIGHT - mBosses[mCurBoss]->getHeight() / 2;

			float x = mBosses[mCurBoss]->getX();
			float y = mBosses[mCurBoss]->getY();
			if (y > yTarget)
			{
				mBosses[mCurBoss]->setPosition(x, y - 64 * frameTime);
			}
			else
			{
				mCurState = State_StartGuns;
			}
		}
		break;

	case State_StartGuns:
		mBosses[mCurBoss]->startGuns();
		mCurState = State_Update;
		break;

	case State_Update:
		break;

	case State_Intermission:
		break;
	}
}

void BossManager::render()
{
	mBosses[mCurBoss]->render();
}