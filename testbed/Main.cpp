#include <cmath>
#include <iostream>
#include <ctime>
#include "bsBulletScript.h"
#include "Main.h"
#include "Platform.h"
#include "RendererGL.h"
#include "BulletSystem.h"
#include "AreaSystem.h"
#include "UnitSystem.h"

#if BS_PLATFORM == BS_PLATFORM_WIN32
#	include <windows.h>
#	include <direct.h>
#	include <io.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>

#if BS_PLATFORM == BS_PLATFORM_LINUX
#	include <stdlib.h>
#	include <sys/time.h>
#	include <time.h>

timeval start_time;

unsigned int timeGetTime()
{
	timeval now;
	unsigned int ticks;
	
	gettimeofday(&now, NULL);
	ticks = (now.tv_sec - start_time.tv_sec) * 1000 + (now.tv_usec - start_time.tv_usec) / 1000;
	return ticks;
}
#endif

using namespace bs;

extern int gTotalBullets;

class GunWrapper
{
	bs::Machine* mMachine;
	bs::Emitter* mGun;
	bs::Controller* mCtrl;
	bool mGunNotCtrl;
	float mTime;
	bool mAlive;

public:

	explicit GunWrapper(bs::Machine* machine) :
		mMachine(machine),
		mAlive(true)
	{
		if (true)//(rand() & 1)
		{
			mGunNotCtrl = true;
			int rr = rand() % 4;
			if (rr == 0)
			{
				mGun = machine->createEmitter("Flower");
				mGun->setX(200 + rand() % 400);
				mGun->setY(200 + rand() % 200);
			}
			else if (rr == 1)
			{
				mGun = machine->createEmitter("Fireworks");
				mGun->setX(100 + rand() % 600);
				mGun->setY(100);
			}
			else if (rr == 2)
			{
				mGun = machine->createEmitter("Abstract");
				mGun->setX(200 + rand() % 400);
				mGun->setY(200 + rand() % 200);
			}
			else if (rr == 3)
			{
				mGun = machine->createEmitter("ShipSpawner");
				mGun->setX(200 + rand() % 400);
				mGun->setY(400 + rand() % 100);
			}

			mTime = 10 + rand() % 18;

			mGun->setAngle(180);
		}
		else
		{
			mGunNotCtrl = false;
			mCtrl = machine->createController("Boss1");

			mCtrl->setX(100 + rand() % 600);
			mCtrl->setY(100 + rand() % 400);
			mCtrl->setAngle(180);
		}
	}

	~GunWrapper()
	{
		if (mGunNotCtrl)
			mMachine->destroyEmitter(mGun);
		else
			mMachine->destroyController(mCtrl);
	}

	void update(float frameTime)
	{
		mTime -= frameTime;
		if (mTime < 0.0f)
			mAlive = false;
	}

	bool isAlive() const
	{
		return mAlive;
	}
};

std::list<GunWrapper*> gWrappers;

int updateWrappers(float frameTime)
{
	int count = 0;
	
	// update
	std::list<GunWrapper*>::iterator it = gWrappers.begin();
	while (it != gWrappers.end())
	{
/*
		std::list<GunWrapper*>::iterator it2 = it; ++it2;
		
		(*it)->update(frameTime);
		if (!(*it)->isAlive())
		{
			gWrappers.erase(it);
			delete *it;
			it = it2;
		}
		else
		{
			++it;
			count++;
		}
*/
		++it;
	}

	return count;
}

void destroyGunWrappers()
{
	std::list<GunWrapper*>::iterator it = gWrappers.begin();
	while (it != gWrappers.end())
	{
		delete *it;
		++it;
	}

	gWrappers.clear();
}

#if BS_PLATFORM == BS_PLATFORM_WIN32
std::vector<String> getDirectoryListing(const String &dir, const String &pattern)
{
	std::vector<String> fileList;
	
	long lHandle, res;
	struct _finddata_t tagData;

	String fullPath = dir + "/" + pattern;

	lHandle = (long) _findfirst (fullPath.c_str (), &tagData);
	res = 0;
	while (lHandle != -1 && res != -1)
	{
		// Don't add directories
		if ((tagData.attrib & _A_SUBDIR) == 0 &&
			(strcmp (tagData.name, ".") && strcmp (tagData.name, "..")))
		{
			String fileName = String (tagData.name);
			fileList.push_back (fileName);
		}

		res = _findnext (lHandle, &tagData);
	}

	// Close if we found any files
	if (lHandle != -1)
		_findclose (lHandle);

	return fileList;
}
#elif BS_PLATFORM == BS_PLATFORM_LINUX
std::vector<String> getDirectoryListing(const String &dir, const String &pattern)
{
	std::vector<String> fileList;
	
	return fileList;
}
#endif

// Load a script file
uint8* loadFile(const String& fileName, size_t& byteSize)
{
	FILE *fp = fopen(fileName.c_str(), "rb");

	if (!fp)
	{
		byteSize = 0;
		return 0;
	}

	fseek(fp, 0, SEEK_END);
	byteSize = ftell(fp);
	
	rewind(fp);
	uint8* buffer = new uint8[byteSize];
	fread(buffer, byteSize, 1, fp);
	fclose(fp);

	return buffer;
}

unsigned int getTicks()
{
#ifdef MINIMAL_APP
	return timeGetTime();
#else
	return SDL_GetTicks();
#endif
}

int main (int argc, char **argv)
{
	int runTime = 999999999;
	if (argc >= 2)
		runTime = atoi(argv[1]) * 1000;

	srand(time(0));

	// Create machine
	Machine machine;

	// Register bullet functions
	machine.createType("bullet");

	machine.registerFireFunction("bullet", "fireA", 2, BulletBattery::emitAngle);
	machine.setDieFunction("bullet", BulletBattery::killBullet);
	machine.registerProperty("bullet", "angle",	BulletBattery::setAngle, BulletBattery::getAngle);
	machine.registerProperty("bullet", "red", BulletBattery::setRed, BulletBattery::getRed);
	machine.registerProperty("bullet", "green",	BulletBattery::setGreen, BulletBattery::getGreen);
	machine.registerProperty("bullet", "blue", BulletBattery::setBlue, BulletBattery::getBlue);
	machine.registerProperty("bullet", "alpha",	BulletBattery::setFade,	BulletBattery::getFade);
	machine.registerAffector("bullet", "Gravity", BulletBattery::gravity);

	// Register area functions
	machine.createType("area");

	machine.registerFireFunction("area", "quadC", 3, AreaBattery::emitQuadC);
	machine.registerFireFunction("area", "quadB", 3, AreaBattery::emitQuadB);
	machine.registerFireFunction("area", "ellipse", 2, AreaBattery::emitEllipse);
	machine.registerFireFunction("area", "arc", 5, AreaBattery::emitArc);
	machine.setDieFunction("area", AreaBattery::killArea);
	machine.registerProperty("area", "alpha", AreaBattery::setFade,	AreaBattery::getFade);
	machine.registerProperty("area", "width", AreaBattery::setWidth, AreaBattery::getWidth);
	machine.registerProperty("area", "height", AreaBattery::setHeight, AreaBattery::getHeight);
	machine.registerProperty("area", "iwidth", AreaBattery::setInnerWidth, AreaBattery::getInnerWidth);
	machine.registerProperty("area", "iheight",	AreaBattery::setInnerHeight, AreaBattery::getInnerHeight);
	machine.registerProperty("area", "angle", AreaBattery::setAngle, AreaBattery::getAngle);
	machine.registerProperty("area", "start", AreaBattery::setStart, AreaBattery::getStart);
	machine.registerProperty("area", "end", AreaBattery::setEnd, AreaBattery::getEnd);

	// Register unit functions
	machine.createType("unit");

	machine.registerFireFunction("unit", "ship1", 0, UnitSystem::emitUnit);
	machine.setDieFunction("unit", UnitSystem::killUnit);

	// Register global variables
	machine.registerGlobalVariable("Level_Time", true, 0);
	machine.registerGlobalVariable("ScreenSize_X", true, SCREEN_WIDTH);
	machine.registerGlobalVariable("ScreenSize_Y", true, SCREEN_HEIGHT);
	machine.registerGlobalVariable("Test_Global", false, 0);

	// User member variables must be declared before compiling scripts
	machine.declareMemberVariable("Boss1", "health", 1); // 100%

	std::cout << "Compiling..." << std::endl;

	// Load file
//	std::vector<String> scriptFiles = getDirectoryListing(".", "*.script");
	std::vector<String> scriptFiles;
	scriptFiles.push_back("Abstract.script");
	scriptFiles.push_back("Basic.script");
	scriptFiles.push_back("Flower.script");
	scriptFiles.push_back("Spawns.script");

	for (size_t i = 0; i < scriptFiles.size(); ++i)
	{
		size_t fileSize;
		uint8* fileBuf = loadFile(scriptFiles[i], fileSize);
		if(machine.compileScript (fileBuf, fileSize) != 0)
		{
			std::cout << "Could not compile " << scriptFiles[i] << std::endl;
			const Log& _log = machine.getLog();

			String msg = _log.getFirst();
			while (msg != Log::END)
			{
				std::cout << msg << std::endl;
				msg = _log.getNext();
			}

			delete[] fileBuf;
			return 0;
		}

		delete[] fileBuf;
	}

	std::cout << "Initialising..." << std::endl;

	// Initialise systems
	BulletBattery::initialise(&machine);
	AreaBattery::initialise(&machine);
	UnitSystem::initialise(&machine);

#ifndef MINIMAL_APP
	RendererGL renderer;
	if (!renderer.initialise(SCREEN_WIDTH, SCREEN_HEIGHT))
		return 0;

	SDL_ShowCursor(SDL_DISABLE);
#endif

/*
	// Create a gun
	Emitter* gun;

	gun = machine.createEmitter("ShipSpawner");
	gun->setX(230);
	gun->setY(400);
	gun->setAngle(180);

	gun = machine.createEmitter("ShipSpawner");
	gun->setX(530);
	gun->setY(400);
	gun->setAngle(180);

	gun = machine.createEmitter("Abstract");
	gun->setX(400);
	gun->setY(500);
	gun->setAngle(180);

	gun = machine.createEmitter("Flower");
	gun->setX(400);
	gun->setY(200);
	gun->setAngle(180);

	gun = machine.createEmitter("Flower");
	gun->setX(650);
	gun->setY(400);
	gun->setAngle(180);

	gun = machine.createEmitter("Flower");
	gun->setX(150);
	gun->setY(400);
	gun->setAngle(180);

	gun = machine.createEmitter("Fireworks");
	gun->setX(10);
	gun->setY(10);
	gun->setAngle(180);

	gun = machine.createEmitter("Fireworks");
	gun->setX(110);
	gun->setY(10);
	gun->setAngle(180);

	gun = machine.createEmitter("Fireworks");
	gun->setX(210);
	gun->setY(10);
	gun->setAngle(180);

	// Create a controller
	Controller* controller = machine.createController("Boss1");
	controller->setX(400);
	controller->setY(300);
	controller->setAngle(180);

	controller = machine.createController("Boss1");
	controller->setX(150);
	controller->setY(140);
	controller->setAngle(180);
*/

	// Main loop
	unsigned int curTime = getTicks();
	unsigned int totalTime = 0;

	unsigned int fpsCounter = 0;
	unsigned int numFrames = 0, updateTime = 0;

	int numBullets = 0;
	int numWrappers = 0;

	float updateCounter = 0;
	float updateFreq = 1 / 60.0f;

	float wrapperCounter;

	bool evtRaised = false;
	while (totalTime < runTime)
	{
#ifndef MINIMAL_APP
		if (!processMessages())
			break;
#endif

		if (!paused())
		{
			// Get update time
			unsigned int newTime = getTicks();
			unsigned int deltaTime = newTime - curTime;

			curTime = newTime;
			
			totalTime += deltaTime;
			fpsCounter += deltaTime;

			float frameTime = deltaTime / 1000.0f;

			if (fpsCounter > 1000)
			{
				fpsCounter -= 1000;
				std::cerr << "Avg update time: " << (updateTime / (float) numFrames) << "ms " << (totalTime/1000.0f) << 
					" FPS: " << numFrames << " Bullets: " << numBullets << "/" << gWrappers.size() << std::endl;
				numFrames = 0;
				updateTime = 0;
			}

			wrapperCounter += frameTime;
			updateCounter += frameTime;

			updateFreq = frameTime;
//			if (updateCounter >= updateFreq) // uncomment this line to run at 60hz
			{
				updateCounter -= updateFreq;

				// Update test wrappers
				numWrappers = updateWrappers(updateFreq);

				// Set script globals - this will update BulletAffector global arguments
				machine.setGlobalVariableValue("Level_Time", totalTime / 1000.0f);

				unsigned int bsTime1 = getTicks();

				// Update machine
				machine.update(updateFreq);

				// Update types
				numBullets = BulletBattery::update(frameTime);
				AreaBattery::update(updateFreq);
				UnitSystem::update(updateFreq);

				unsigned int bsTime2 = getTicks();

				updateTime += (bsTime2 - bsTime1);
			}

			numFrames++;
		}

		if (wrapperCounter > 0.3)
		{
			if (numBullets < 50000)
			{
				GunWrapper* wr = new GunWrapper(&machine);
				gWrappers.push_back(wr);
			}
			wrapperCounter -= 0.3;
		}

		// Render
#ifndef MINIMAL_APP
		renderer.startRendering();

		BulletBattery::render(&renderer);
		AreaBattery::render(&renderer);
		UnitSystem::render(&renderer);

		renderer.finishRendering();
#endif

	}

	UnitSystem::shutdown();

#ifndef MINIMAL_APP
	SDL_Quit();
#endif
	
	destroyGunWrappers();
	return 0;
}
