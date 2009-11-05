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
	Machine<Bullet, Area, SoundEffect, Unit> machine("bullet", "area", "sound", "unit");

	// Register bullet functions
	machine.registerFireFunction<Bullet>("fireA", 2,	BulletBattery::emitAngle);
	machine.setDieFunction<Bullet>(BulletBattery::killBullet);
	machine.registerProperty<Bullet>("angle",	BulletBattery::setAngle,		BulletBattery::getAngle);
	machine.registerProperty<Bullet>("red",		BulletBattery::setRed,			BulletBattery::getRed);
	machine.registerProperty<Bullet>("green",	BulletBattery::setGreen,		BulletBattery::getGreen);
	machine.registerProperty<Bullet>("blue",	BulletBattery::setBlue,			BulletBattery::getBlue);
	machine.registerProperty<Bullet>("alpha",	BulletBattery::setFade,			BulletBattery::getFade);
	machine.registerAffector<Bullet>("gravity", BulletBattery::gravity);

	// Register area functions
	machine.registerFireFunction<Area>("quadC", 3,		AreaBattery::emitQuadC);
	machine.registerFireFunction<Area>("quadB", 3,		AreaBattery::emitQuadB);
	machine.registerFireFunction<Area>("ellipse", 2,	AreaBattery::emitEllipse);
	machine.registerFireFunction<Area>("arc", 5,		AreaBattery::emitArc);
	machine.setDieFunction<Area>(AreaBattery::killArea);
	machine.registerProperty<Area>("alpha",		AreaBattery::setFade,			AreaBattery::getFade);
	machine.registerProperty<Area>("width",		AreaBattery::setWidth,			AreaBattery::getWidth);
	machine.registerProperty<Area>("height",	AreaBattery::setHeight,			AreaBattery::getHeight);
	machine.registerProperty<Area>("iwidth",	AreaBattery::setInnerWidth,		AreaBattery::getInnerWidth);
	machine.registerProperty<Area>("iheight",	AreaBattery::setInnerHeight,	AreaBattery::getInnerHeight);
	machine.registerProperty<Area>("angle",		AreaBattery::setAngle,			AreaBattery::getAngle);
	machine.registerProperty<Area>("start",		AreaBattery::setStart,			AreaBattery::getStart);
	machine.registerProperty<Area>("end",		AreaBattery::setEnd,			AreaBattery::getEnd);

	// Register audio functions
	machine.registerFireFunction<SoundEffect>("fx", 2,	AudioSystem::emitSound);
	machine.setDieFunction<SoundEffect>(AudioSystem::killSound);
	machine.registerProperty<SoundEffect>("volume", AudioSystem::setVolume,		AudioSystem::getVolume);

	// Register unit functions
	machine.registerFireFunction<Unit>("ship1", 0,		UnitSystem::emitUnit);
	machine.setDieFunction<Unit>(UnitSystem::killUnit);

	// Register global variables
	machine.registerGlobalVariable("Level_Time", 0);
	machine.registerGlobalVariable("ScreenSize_X", SCREEN_WIDTH);
	machine.registerGlobalVariable("ScreenSize_Y", SCREEN_HEIGHT);

	// User member variables must be declared before compiling scripts
//	machine.declareMemberVariable("Test", "health", 100);

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

	Gun* gun;

	// Create a gun

	for (int i = 0; i < 1; ++i)
	{
		gun = machine.createGun("Flower");
		gun->setX(400);
		gun->setY(300);
		gun->setAngle(180);
	}
/*
	gun = machine.createGun("Beam");
	gun->setX(GUN_X);
	gun->setY(GUN_Y - 100);
	gun->setAngle(180);
*/
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