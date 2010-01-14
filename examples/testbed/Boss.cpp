#include "Boss.h"
#include "Bosses.h"
#include "RendererGL.h"

extern BulletBattery* g_bossBullets, *g_playerBullets;

Boss::Boss(bs::Machine* machine) :
	mTexture(0),
	mWidth(0),
	mHeight(0),
	mBoundsX0(0),
	mBoundsY0(0),
	mBoundsX1(0),
	mBoundsY1(0),
	mX(0),
	mY(0),
	mAngle(0),
	mHealth(100),
	mGunController(0),
	mMachine(machine),
	mVisible(false)
{
}

Boss::~Boss()
{
	stopGuns();
}

void Boss::reset()
{
	mHealth = 100;
}

void Boss::setVisible(bool vis)
{
	mVisible = vis;
}

void Boss::loadImage()
{
	TGALoader img(mImageFile);
	mTexture = img.loadToVRAM (mWidth, mHeight);
}

void Boss::setBounds(int x0, int y0, int x1, int y1)
{
	mBoundsX0 = x0;
	mBoundsY0 = y0;
	mBoundsX1 = x1;
	mBoundsY1 = y1;
}

void Boss::setGuns(const char* guns)
{
	mGunController = mMachine->createController(guns, g_bossBullets);
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

void Boss::setHealth(int health)
{
	mHealth = health;
}

int Boss::getHealth() const
{
	return mHealth;
}

void Boss::startGuns()
{
	setGuns("Boss1");
}

void Boss::stopGuns()
{
	if (mGunController)
	{
		mMachine->destroyController(mGunController);
		mGunController = 0;
	}
}

bool Boss::checkCollisions(BulletBattery* bs)
{
	int hits = bs->checkCollisions(mX - mBoundsX0, mY - mBoundsY0, mX + mBoundsX1, mY + mBoundsY1);
	if (!damage(hits))
	{
		// Kill, alert BossManager
		return true;
	}

	return false;
}

void Boss::render()
{
	if (!mVisible)
		return;

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




BossManager::BossManager(bs::Machine* machine) :
	mCurBoss(0),
	mCurState(State_Setup),
	mIdle(-1.0f)
{

	mBosses[0] = new Boss1(machine);
	mBosses[1] = new Boss2(machine);
}

BossManager::~BossManager()
{
	for (int i = 0; i < NUM_BOSSES; ++i)
		delete mBosses[i];
}

void BossManager::loadImages()
{
	for (int i = 0; i < NUM_BOSSES; ++i)
		mBosses[i]->loadImage();
}

void BossManager::update(float frameTime)
{
	switch(mCurState)
	{
	case State_Setup:
		mBosses[mCurBoss]->reset();
		mBosses[mCurBoss]->setVisible(true);
		mBosses[mCurBoss]->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT + 100);
		mBosses[mCurBoss]->setAngle(0);
		mCurState = State_MoveOnScreen;
		break;

	case State_MoveOnScreen:
		{
			int yTarget = SCREEN_HEIGHT - mBosses[mCurBoss]->getHeight() / 2;

			float x = mBosses[mCurBoss]->getX();
			float y = mBosses[mCurBoss]->getY();
			if (y > yTarget)
			{
				mBosses[mCurBoss]->setPosition(x, y - 96 * frameTime);
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
		mBosses[mCurBoss]->update(frameTime);
		checkCollisions(g_playerBullets);
		break;

	case State_Intermission:
		mIdle -= frameTime;
		if (mIdle < 0.0f)
			mCurState = State_Setup;
		break;
	}
}

void BossManager::checkCollisions(BulletBattery* bs)
{
	bool dead = mBosses[mCurBoss]->checkCollisions(bs);
	if (dead)
	{
		mBosses[mCurBoss]->setVisible(false);
		mBosses[mCurBoss]->stopGuns();

		mCurBoss++;
		if (mCurBoss == NUM_BOSSES)
			mCurBoss = 0;

		mBosses[mCurBoss]->setHealth(0);
		mIdle = 3.0f;
		mCurState = State_Intermission;
	}
}

void BossManager::render()
{
	float cx = SCREEN_WIDTH / 2 - 128;
	float cy = SCREEN_HEIGHT - 12;
	mBosses[mCurBoss]->render();

	float scale;
	if (mCurState == State_Intermission)
	{
		scale = (3.0f - mIdle) / 3.0f;
	}
	else
	{
		int health = mBosses[mCurBoss]->getHealth();
		scale = health / 100.0f;
	}

	// Render health bar
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	{
			glVertex2f(cx, cy - 8);
			glVertex2f(cx + 256 * scale, cy - 8);
			glVertex2f(cx + 256 * scale, cy + 8);
			glVertex2f(cx, cy + 8);
	}
	glEnd();

	glBegin(GL_LINES);
	{
			glVertex2f(cx, cy - 8 - 2);
			glVertex2f(cx + 256, cy - 8 - 2);
			glVertex2f(cx, cy + 8 + 2);
			glVertex2f(cx + 256, cy + 8 + 2);
	}
	glEnd();
}