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
		if (false/*rand() & 1*/)
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
};

std::list<GunWrapper*> gWrappers;

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

void plotValues(const std::vector<float> time1, const std::vector<float> time2)
{
	// find fps range
	float minT = 9999999, maxT = -1, rangeT;
	for (size_t i = 0; i < time1.size(); ++i)
	{
		if (time1[i] > maxT)
			maxT = time1[i];
		if (time1[i] < minT)
			minT = time1[i];
	}
	rangeT = maxT - minT;
	int iRange = (int) (rangeT * 100.0f);

	int height = iRange;
	int width = time1.size();

	std::cerr << "plot: " << width << "x" << height << std::endl;

	unsigned char* image = new unsigned char[height * width];
	memset(image, 255, height * width);

	for (size_t i = 0; i < time1.size(); ++i)
	{
		int offset = (int) ((time1[i] - minT) * 100.0f);
		offset = offset * width + i;
		image[offset] = 0;
	}

	// now do small time
	float minT2 = 9999999, maxT2 = -1, rangeT2;
	for (size_t i = 0; i < time2.size(); ++i)
	{
		if (time2[i] > maxT2)
			maxT2 = time2[i];
		if (time2[i] < minT2)
			minT2 = time2[i];
	}
	rangeT2 = maxT2 - minT2;
	// scale to large time
	float scaleFac = rangeT / rangeT2;

//	std::cerr << rangeT2 << " " << rangeT << " " << scaleFac << std::endl;
	for (size_t i = 0; i < time2.size(); ++i)
	{
		int offset = (int) ((time2[i] - minT2) * scaleFac * 100.0f);
		offset = offset * width + i;
		image[offset] = 150;
	}

	FILE* fp = fopen("plot.raw", "wb");
	fwrite(image, height * width, sizeof(unsigned char), fp);
	fclose(fp);
	delete[] image;
}

/*
FILE* open_profile_file(const char* fileName)
{
	FILE* fp = fopen(fileName, "a+");
	fprintf(fp, "Timestamp (s)\tUpdate length (ms)\tFPS\tbullets\n");
	fprintf(fp, "-------------------------------------------------------\n");
	return fp;
}

void close_profile_file(FILE** fp)
{
	fprintf(*fp, "\n");
	fclose(*fp);
	*fp = 0;
}

void write_profile_info(FILE* fp, float time, float length, int fps, int bullets)
{
	fprintf(fp, "%3.2f\t\t%4.3f\t\t\t%d\t%d\n", time, length, fps, bullets);
}
*/
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

	srand(999);

	// Create machine
	Machine machine;

	// Register bullet functions
	machine.createType("bullet");

	machine.registerEmitFunction("bullet", "fireA", 2, BulletBattery::emitAngle);
	machine.setDieFunction("bullet", BulletBattery::killBullet);
	machine.registerProperty("bullet", "angle",	BulletBattery::setAngle, BulletBattery::getAngle);
	machine.registerProperty("bullet", "red", BulletBattery::setRed, BulletBattery::getRed);
	machine.registerProperty("bullet", "green",	BulletBattery::setGreen, BulletBattery::getGreen);
	machine.registerProperty("bullet", "blue", BulletBattery::setBlue, BulletBattery::getBlue);
	machine.registerProperty("bullet", "alpha",	BulletBattery::setFade,	BulletBattery::getFade);
	machine.registerAffector("bullet", "Gravity", BulletBattery::gravity);

	// Register area functions
	machine.createType("area");

	machine.registerEmitFunction("area", "quadC", 3, AreaBattery::emitQuadC);
	machine.registerEmitFunction("area", "quadB", 3, AreaBattery::emitQuadB);
	machine.registerEmitFunction("area", "ellipse", 2, AreaBattery::emitEllipse);
	machine.registerEmitFunction("area", "arc", 5, AreaBattery::emitArc);
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

	machine.registerEmitFunction("unit", "ship1", 0, UnitSystem::emitUnit);
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
	std::vector<String> scriptFiles = getDirectoryListing(".", "*.script");

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

	// Main loop
	unsigned int curTime = getTicks();
	unsigned int totalTime = 0;

	unsigned int fpsCounter = 0;
	unsigned int numFrames = 0, updateTime0 = 0, updateTime2 = 0;

	int numBullets = 0;

	// 50 emitters to start
	for (int i = 0; i < 1; ++i)
	{
		GunWrapper* wr = new GunWrapper(&machine);
		gWrappers.push_back(wr);
	}

	while (true)
	{
#ifndef MINIMAL_APP
		if (!processMessages())
			break;
#endif

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

			int fps = numFrames;
			float updateMS2 = (updateTime2 / (float) numFrames);
			std::cerr << "Avg update time: " << updateMS2 << "ms " << (totalTime/1000.0f) << 
				" FPS: " << fps << " " << numBullets << "/" << gWrappers.size() << std::endl;

			numFrames = 0;
			updateTime0 = 0;
			updateTime2 = 0;
		}

		// Set script globals - this will update BulletAffector global arguments
		machine.setGlobalVariableValue("Level_Time", totalTime / 1000.0f);

		// Update machine
		machine.update(frameTime);

		unsigned int bsTime2 = getTicks();

		// Update types
		updateTime0 += BulletBattery::update(frameTime, &numBullets);
		AreaBattery::update(frameTime);
		UnitSystem::update(frameTime);

		unsigned int bsTime3 = getTicks();
		updateTime2 += (bsTime3 - bsTime2);

		numFrames++;

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
	
//	close_profile_file(&prof);

	destroyGunWrappers();
	return 0;
}
