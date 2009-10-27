#include <iostream>
#include <cmath>
#include "bsBulletScript.h"
#include "BulletSystem.h"

#if BS_PLATFORM == BS_PLATFORM_WIN32
#	include <windows.h>
#endif

#if BS_PLATFORM == BS_PLATFORM_LINUX
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

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

using namespace BS;
using namespace std;

extern int gBulletsEmitted;

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

// --------------------------------------------------------------------------------
// Main
// --------------------------------------------------------------------------------

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		cout << "No file/time specified." << endl;
		return 0;
	}

#if BS_PLATFORM == BS_PLATFORM_LINUX
	gettimeofday(&start_time, NULL);
#endif

	// Create machine
	Machine<Bullet> machine("bullet");

	// Register global variables
	machine.registerGlobalVariable("Level_Time", 0);

	// Register bullet functions
	machine.registerFireFunction<Bullet>("fireA", 2, BulletBattery::emitAngle);
	machine.setDieFunction<Bullet>(BulletBattery::killBullet);
	machine.registerProperty<Bullet>("angle", BulletBattery::setAngle, BulletBattery::getAngle);

	// Add extra member variables
//	machine.declareMemberVariable("Test", "health", 100);

	std::cout << "Compiling..." << std::endl;

	// Load script file
	size_t fileSize;
	std::auto_ptr<uint8> fb(loadFile(argv[1], fileSize));
	if (machine.compileScript(fb.get(), fileSize) != 0)
	{
		cout << "Could not compile " << argv[1] << endl;
		const Log& _log = machine.getLog();

		String msg = _log.getFirst();
		while (msg != Log::END)
		{
			cout << msg << endl;
			msg = _log.getNext();
		}

		return 0;
	}

	// Initialise
	std::cout << "Initialising..." << std::endl;
	BulletBattery::initialise(&machine);

	// Create a gun
	Gun* gun = machine.createGun("Test");
	gun->setMemberVariable(Member_X, 400);
	gun->setMemberVariable(Member_Y, 540);
	gun->setMemberVariable(Member_Angle, 180);

	// Timing
	unsigned long curTime = timeGetTime();
	unsigned long totalTime = 0;
	unsigned long runTime = atof(argv[2]) * 1000;
	unsigned long statCounter = 0;
	unsigned long frameCounter = 0;

	// Frame limiting
	float updateCounter = 0;
	float updateFreq = 1 / 60.0f;
	bool updateLogic = false;

	// Go!
	while (totalTime < runTime)
	{
		unsigned long deltaTime = timeGetTime() - curTime;
		totalTime += deltaTime;
		curTime += deltaTime;
		statCounter += deltaTime;

		float frameTime = deltaTime / 1000.0f;

		// Set global script variables
		machine.setGlobalVariableValue("Level_Time", totalTime / 1000.0f);

		// Update system
//		updateCounter += frameTime;
//		if (updateCounter >= updateFreq)
//		{
//			updateCounter -= updateFreq;

			// Update machine
			machine.update(frameTime);

			// Update bullets
			BulletBattery::update(frameTime);
//		}

		frameCounter++;	

		if (statCounter >= 1000)
		{
			int bullets, spawned, killed;
			BulletBattery::getStats(bullets, spawned, killed);
			cout << "[" << frameCounter << "] " << bullets << " bullets, " << spawned << " spawned and " 
				<< killed << " killed in the last second." << endl;

			statCounter -= 1000;
			frameCounter = 0;
		}
	}

	return 0;
}
