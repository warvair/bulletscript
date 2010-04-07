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

//				std::cout << "bullet emitted at " << args[-1] << " " << args[-2] << " " << args[-3] << std::endl;
				std::cout << "bullet emitted" << std::endl;
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
//	gBullets->addBullet(x, y, angle, 0);
//	std::cerr << "ok! " << x << " " << y << " " << angle << " " << args[0] << " " <<
//		args[1] << " " << args[2] << std::endl;
	std::cerr << "ok " << x << " " << y << " " << args <<std::endl;
	return 0;
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



///////////////////////////////////////////////////////////////////////////////
// Main
///////////////////////////////////////////////////////////////////////////////
int main()
{
	gMachine = new bs::Machine;
	gBullets = new BulletManager;

	// Enable jit
	if (!gMachine->enableJIT("bsjit.dll"))
	{
		// get errors
		const bs::Log& _log = gMachine->getLog();

		std::string msg = _log.getFirstEntry();
		while (msg != bs::Log::END)
		{
			std::cerr << msg << std::endl;
			msg = _log.getNextEntry();
		}

		delete gBullets;
		delete gMachine;
	}

	// Bind type
	gMachine->createType("bullet");
	gMachine->registerEmitFunction("bullet", "emit", 3, emitBullet);
	gMachine->setDieFunction("bullet", killBullet);
	
	gMachine->setAnchorX("bullet", setX, getX);
	gMachine->setAnchorY("bullet", setY, getY);
	gMachine->setAnchorAngle("bullet", setAngle, getAngle);

	// Compile script - open in binary mode because sometimes ftell messes up in text mode
	FILE* fp = fopen("test.script", "rb");
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

	std::cerr << "Compiled." << std::endl;

	// Create an emitter
	bs::Emitter* emit = gMachine->createEmitter("Test", 20, 30, 40);

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