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

	// Register fire functions
	machine.registerFireFunction<Bullet>("fireA", 3, BulletBattery::emitAngle);

	// Add extra member variables
	// ...

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

	// Create a gun
	Gun* gun = machine.createGun("Test");
	gun->setMemberVariable(Member_X, 300);
	gun->setMemberVariable(Member_Y, 400);
	gun->setMemberVariable(Member_Angle, 180);

	unsigned long curTime = timeGetTime();
	unsigned long totalTime = 0;
	unsigned long numFrames = 0;
	unsigned long runTime = atof(argv[2]) * 1000;
	while (totalTime < runTime)
	{
		unsigned long deltaTime = timeGetTime() - curTime;
		totalTime += deltaTime;
		curTime += deltaTime;

		float frameTime = deltaTime / 1000.0f;

		// Set global script variables
		machine.setGlobalVariableValue("Level_Time", totalTime / 1000.0f);

		// Update the machine - this updates Guns
		machine.update(frameTime);

		int numBullets = BulletBattery::update(frameTime, &machine);
//		std::cout << numBullets << std::endl;
//		std::cout << runTime << " " << totalTime << std::endl;
		numFrames++;	
	}

	cout << totalTime << " " << numFrames << endl;
//	float fps = (float) numFrames / (totalTime / 1000.0f);
//	cout << fps << endl;

	return 0;
}
