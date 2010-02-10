#ifdef _WIN32
#	include <windows.h>
#endif
#include <iostream>
#include <cmath>
#include "bsBulletScript.h"

#define DEG_TO_RAD (3.14159 / 180.0)

///////////////////////////////////////////////////////////////////////////////
// Bullet structure
///////////////////////////////////////////////////////////////////////////////
struct Bullet : public bs::UserTypeBase
{
	float x, y;
	float angle;
	float speed;
	
	bool _active;
};




///////////////////////////////////////////////////////////////////////////////
// Bullet management class
///////////////////////////////////////////////////////////////////////////////
bs::Machine* gMachine = 0;

class BulletManager
{
	static const int NUM_BULLETS = 1024;

	Bullet mBullets[NUM_BULLETS];

public:

	BulletManager()
	{
		for (int i = 0; i < NUM_BULLETS; ++i)
			mBullets[i]._active = false;
	}

	bs::UserTypeBase* BulletManager::addBullet(float x, float y, float angle, const float* args)
	{
		// Find first free slot
		for (int i = 0; i < NUM_BULLETS; ++i)
		{
			if (!mBullets[i]._active)
			{
				mBullets[i]._active = true;

				mBullets[i].x = x;
				mBullets[i].y = y;
				mBullets[i].angle = angle;

				// Important: the argument array is in fact the top of a stack.  
				// Thus, arguments have negative indices.  
				// The first argument is at args[-num_args], and the last at args[-1].		

				// Assume that the bullet speed is passed in the first argument.
				mBullets[i].speed = args[-1];

				std::cout << "bullet emitted." << std::endl;
				return &mBullets[i];
			}
		}

		// If we get here, there are no free slots
		return 0;
	}

	void killBullet(Bullet* b)
	{
		std::cout << "bullet killed." << std::endl;
		b->_active = false;
	}

	void update(float frameTime)
	{
		for (int i = 0; i < NUM_BULLETS; ++i)
		{
			if (mBullets[i]._active)
			{
				// Assume angle is in radians
				mBullets[i].x += (float) sin(mBullets[i].angle * DEG_TO_RAD) * mBullets[i].speed * frameTime;
				mBullets[i].y += (float) cos(mBullets[i].angle * DEG_TO_RAD) * mBullets[i].speed * frameTime;

				// Now, we tell bulletscript to update our objects.
				gMachine->updateType(&mBullets[i], mBullets[i].x, mBullets[i].y, mBullets[i].angle, frameTime);
			}
		}
	}
};




///////////////////////////////////////////////////////////////////////////////
// Function hooks
///////////////////////////////////////////////////////////////////////////////
BulletManager* gBullets = 0;

bs::UserTypeBase* emitBullet(float x, float y, float angle, const float* args, void* user)
{
	return gBullets->addBullet(x, y, angle, args);
}

void killBullet(bs::UserTypeBase *userType, void* user)
{
	Bullet* b = static_cast<Bullet*>(userType);
	gBullets->killBullet(b);
}

void setX(bs::UserTypeBase* userType, float value)
{
	Bullet* b = static_cast<Bullet*>(userType);
	b->x = value;
}

float getX(bs::UserTypeBase* userType)
{
	Bullet* b = static_cast<Bullet*>(userType);
	return b->x;
}

void setY(bs::UserTypeBase* userType, float value)
{
	Bullet* b = static_cast<Bullet*>(userType);
	b->y = value;
}

float getY(bs::UserTypeBase* userType)
{
	Bullet* b = static_cast<Bullet*>(userType);
	return b->y;
}

void setAngle(bs::UserTypeBase* userType, float value)
{
	Bullet* b = static_cast<Bullet*>(userType);
	b->angle = value;
}

float getAngle(bs::UserTypeBase* userType)
{
	Bullet* b = static_cast<Bullet*>(userType);
	return b->angle;
}

void setSpeed(bs::UserTypeBase* userType, float value)
{
	Bullet* b = static_cast<Bullet*>(userType);
	b->speed = value;
}

float getSpeed(bs::UserTypeBase* userType)
{
	Bullet* b = static_cast<Bullet*>(userType);
	return b->speed;
}

void accelerate(bs::UserTypeBase* userType, float frameTime, const float* args)
{
	Bullet* b = static_cast<Bullet*>(userType);

	// Like emit functions, affector arguments are specified negatively.
	// First argument here is the acceleration amount, and we multiply
	// this by the supplied frame time, in seconds.
	b->speed += args[-1] * frameTime;
}	




///////////////////////////////////////////////////////////////////////////////
// Main
///////////////////////////////////////////////////////////////////////////////
int main()
{
	gMachine = new bs::Machine;
	gBullets = new BulletManager;

	// Bind type
	gMachine->createType("bullet");
	gMachine->registerEmitFunction("bullet", "emit", 1, emitBullet);
	gMachine->setDieFunction("bullet", killBullet);
	
	gMachine->setAnchorX("bullet", setX, getX);
	gMachine->setAnchorY("bullet", setY, getY);
	gMachine->setAnchorAngle("bullet", setAngle, getAngle);
	gMachine->registerProperty("bullet", "speed", setSpeed, getSpeed);

	gMachine->registerAffector("bullet", "accelerate", accelerate);

	// Compile script - open in binary mode because sometimes ftell messes up in text mode
	FILE* fp = fopen("minimal.script", "rb");
	fseek(fp, 0, SEEK_END);
	size_t fileLength = ftell(fp);
	unsigned char* buffer = new unsigned char[fileLength];
	
	fseek(fp, 0, SEEK_SET);
	fread(buffer, fileLength, 1, fp);
	fclose(fp);

	if (gMachine->compileScript(buffer, fileLength) != 0)
	{
		// get errors
		const bs::Log& _log = gMachine->getLog();

		std::string msg = _log.getFirstEntry();
		while (msg != bs::Log::END)
		{
			std::cerr << msg << std::endl;
			msg = _log.getNextEntry();
		}

		delete[] buffer;
		delete gBullets;
		delete gMachine;
		return 0;
	}
	delete[] buffer;
/*
	fp = fopen("minimal2.script", "rb");
	fseek(fp, 0, SEEK_END);
	fileLength = ftell(fp);
	buffer = new unsigned char[fileLength];
	
	fseek(fp, 0, SEEK_SET);
	fread(buffer, fileLength, 1, fp);
	fclose(fp);

	if (gMachine->compileScript(buffer, fileLength) != 0)
	{
		// get errors
		const bs::Log& _log = gMachine->getLog();

		std::string msg = _log.getFirstEntry();
		while (msg != bs::Log::END)
		{
			std::cerr << msg << std::endl;
			msg = _log.getNextEntry();
		}

		delete[] buffer;
		delete gBullets;
		delete gMachine;
		return 0;
	}
	delete[] buffer;
*/
	// Create an emitter
	bs::Emitter* emit = gMachine->createEmitter("Minimal", 0, 0, 0);

	// Start processing
	unsigned int timer = timeGetTime();
	unsigned int lastTime = timer;
	while (true)
	{
		timer = timeGetTime();
		float frameTime = (timer - lastTime) / 1000.0f;

		gMachine->preUpdate(frameTime);
		gBullets->update(frameTime);
		gMachine->postUpdate(frameTime);

		lastTime = timer;
		Sleep(5);
	}

	delete gBullets;
	delete gMachine;
	return 0;
}