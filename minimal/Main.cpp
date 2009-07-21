#include <iostream>
#include <cmath>
#include "bsScriptMachine.h"
#include "bsBulletMachine.h"
#include "bsBulletGun.h"
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

void script_err(const char* msg)
{
	cerr << msg << endl;
}

// --------------------------------------------------------------------------------
// Main
// --------------------------------------------------------------------------------

int main(int argc, char** argv)
{
	if (argc < 4)
	{
		cout << "No file/guns/run length specified." << endl;
		return 0;
	}

#if BS_PLATFORM == BS_PLATFORM_LINUX
	gettimeofday(&start_time, NULL);
#endif
	
	// Create BulletMachine
	BulletMachine<Bullet> bm;
	bm.registerAffectorFunction("Accel", BulletAffector_Accel);
	bm.registerAffectorFunction("Force", BulletAffector_Force);
	bm.registerAffectorFunction("DelayAccel", BulletAffector_DelayAccel);
	bm.registerAffectorFunction("Explode", BulletAffector_Explode);

	// Create ScriptMachine
	ScriptMachine sm(script_err, &bm);
	sm.registerGlobalVariable("Player_X", 400);
	sm.registerGlobalVariable("Player_Y", 32);
	sm.registerGlobalVariable("Level_Time", 0.0f);
	sm.registerGlobalVariable("ScreenSize_X", 800.0f);
	sm.registerGlobalVariable("ScreenSize_Y", 600.0f);
	sm.registerGlobalVariable("Bullet_Count", 1.0f);
	sm.registerFireFunction("fireA", BulletBattery::emitAngle);
	sm.registerFireFunction("fireT", BulletBattery::emitTarget);

	// Load script file
	size_t fileSize;
	uint8* fileBuf = loadFile(argv[1], fileSize);
	if (sm.compileScript(fileBuf, fileSize) != 0)
	{
		cout << "Could not compile " << argv[1] << endl;
		delete[] fileBuf;
		return 0;
	}

	delete[] fileBuf;

	// Create guns
	std::vector<BulletGunController<Bullet>*> guns;
	int numGuns = atoi(argv[2]);
	for (int i = 0; i < numGuns; ++i)
	{
		BulletGunController<Bullet>* gun = new BulletGunController<Bullet>(&sm, &bm, 0);
		gun->setDefinition("Swarm");
		gun->setInstanceVariable(BS::Instance_Gun_X, 400 + (rand() % 200) - 100);
		gun->setInstanceVariable(BS::Instance_Gun_Y, 300);
		gun->setInstanceVariable(BS::Instance_Gun_Angle, 180 + (rand() % 40) - 20);
		guns.push_back(gun);
	}

	unsigned long curTime = timeGetTime();
	unsigned long totalTime = 0;
	unsigned long runTime = atof(argv[3]) * 1000;
//	int targetCount = atoi(argv[2]);
	while (totalTime < runTime)
//	while (gBulletsEmitted < 10000000)
	{
		unsigned long deltaTime = timeGetTime() - curTime;
		totalTime += deltaTime;
		curTime += deltaTime;

		float frameTime = deltaTime / 1000.0f;

		// Set global script variables
		sm.setGlobalVariableValue("Level_Time", totalTime / 1000.0f);

		// Update affector function arguments
		bm.update();

		// Update guns
		for (int i = 0; i < numGuns; ++i)
		{
			guns[i]->update(frameTime);		// Update affector instance arguments
			guns[i]->runScript(frameTime);	// Run script
		}

		// Update emitted bullets
		int numBullets = BulletBattery::update(frameTime, &bm);
//		cout << numBullets << " / " << gBulletsEmitted << endl;
	}

	cout << totalTime << endl;

	for (int i = 0; i < numGuns; ++i)
		delete guns[i];

	return 0;
}
