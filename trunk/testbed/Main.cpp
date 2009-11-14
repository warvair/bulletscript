#include <cmath>
#include <iostream>
#include <ctime>
#include "bsBulletScript.h"
#include "Main.h"
#include "Platform.h"
#include "RendererGL.h"
#include "BulletSystem.h"
#include "AreaSystem.h"
#include "AudioSystem.h"
#include "UnitSystem.h"

#if BS_PLATFORM == BS_PLATFORM_WIN32
#	include <windows.h>
#endif

#define GUN_X	(SCREEN_WIDTH / 2)
#define GUN_Y	(SCREEN_HEIGHT * 0.9)

using namespace bs;

extern int gTotalBullets;

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

int main (int argc, char **argv)
{
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

	// Register audio functions
	machine.createType("sound");

	machine.registerFireFunction("sound", "fx", 2, AudioSystem::emitSound);
	machine.setDieFunction("sound", AudioSystem::killSound);
	machine.registerProperty("sound", "volume", AudioSystem::setVolume,	AudioSystem::getVolume);

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
	size_t fileSize;
	uint8* fileBuf = loadFile("Guns.script", fileSize);
	if(machine.compileScript (fileBuf, fileSize) != 0)
	{
		std::cout << "Could not compile Guns.script"  << std::endl;
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

	std::cout << "Initialising..." << std::endl;

	// Initialise systems
	BulletBattery::initialise(&machine);
	AreaBattery::initialise(&machine);
	AudioSystem::initialise(&machine);
	UnitSystem::initialise(&machine);

	// Renderer
	RendererGL renderer;
	if (!renderer.initialise(SCREEN_WIDTH, SCREEN_HEIGHT))
		return 0;

	SDL_ShowCursor(SDL_DISABLE);

	// Print interface commands
	std::cout << std::endl;
	std::cout << "BulletScript" << std::endl;
	std::cout << "---------------------" << std::endl;
	std::cout << "[Esc] Quit." << std::endl;
	std::cout << "[Mouse, cursors] Move ship." << std::endl;

	// Create a gun
//	Emitter* gun = machine.createEmitter("Flower");
//	gun->setX(400);
//	gun->setY(300);
//	gun->setAngle(180);

	// Create a controller
	Controller* controller = machine.createController("Boss1");
	controller->setX(400);
	controller->setY(300);
	controller->setAngle(180);

	// Main loop
	unsigned int curTime = SDL_GetTicks();
	unsigned int totalTime = 0;

	unsigned int fpsCounter = 0;
	unsigned int numFrames = 0;

	int numBullets = 0;

	int moveDir = -1;
	int oldX = -10000, oldY = -10000;
	int mouseX = oldX, mouseY = oldY;

	float updateCounter = 0;
	float updateFreq = 1 / 60.0f;
	bool updateLogic = false;

	int lastSel = -1, curSel = -1;

	bool evtRaised = false;
	while (true)
	{
		if (!processMessages())
			break;

		// Get update time
		unsigned int deltaTime = 0;
		unsigned int newTime = 0;
//		while (deltaTime < 1)
		{
			newTime = SDL_GetTicks();
			deltaTime = newTime - curTime;
		}

		curTime = newTime;
		numFrames++;
		
		totalTime += deltaTime;
		fpsCounter += deltaTime;

		float frameTime = deltaTime / 1000.0f;

		// Set script globals - this will update BulletAffector global arguments
		machine.setGlobalVariableValue("Level_Time", totalTime / 1000.0f);

		if (totalTime > 10000 && !evtRaised)
		{
			float damage = 0.5f;
			controller->raiseEvent("Damaged", &damage);
			evtRaised = true;
		}

		if (!paused())
		{
			if (fpsCounter > 1000)
			{
				fpsCounter -= 1000;
				std::cerr << (totalTime/1000.0f) << " FPS: " << numFrames << " Bullets: " << numBullets << "/" << gTotalBullets << std::endl;
				numFrames = 0;
			}

			updateCounter += frameTime;
			if (updateCounter >= updateFreq)
			{
				updateCounter -= updateFreq;
				updateLogic = true;
			}
			else
			{
				updateLogic = false;
			}

			if (updateLogic)
			{
				// Update machine
				machine.update(updateFreq);

				// Update types
				numBullets = BulletBattery::update(updateFreq);
				AreaBattery::update(updateFreq);
				AudioSystem::update(updateFreq);
				UnitSystem::update(updateFreq);
			}
		}

		// Render
		renderer.startRendering();

		BulletBattery::render(&renderer);
		AreaBattery::render(&renderer);
		UnitSystem::render(&renderer);

		renderer.finishRendering();
	}

	AudioSystem::shutdown();
	UnitSystem::shutdown();

	SDL_Quit();
	return 0;
}