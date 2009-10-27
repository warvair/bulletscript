#include <cmath>
#include <iostream>
#include <ctime>
#include "bsBulletScript.h"
#include "Main.h"
#include "Platform.h"
#include "RendererGL.h"
#include "BulletSystem.h"

#if BS_PLATFORM == BS_PLATFORM_WIN32
#	include <windows.h>
#endif

#define GUN_X	(SCREEN_WIDTH / 2)
#define GUN_Y	(SCREEN_HEIGHT * 0.9)

using namespace BS;

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
	Machine<Bullet> machine("bullet");

	// Register global variables
	machine.registerGlobalVariable("Level_Time", 0);

	// Register bullet functions
	machine.registerFireFunction<Bullet>("fireA", 2, BulletBattery::emitAngle);
	machine.setDieFunction<Bullet>(BulletBattery::killBullet);
	machine.registerProperty<Bullet>("angle", BulletBattery::setAngle, BulletBattery::getAngle);
	machine.registerProperty<Bullet>("fade", BulletBattery::setFade, BulletBattery::getFade);

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

	// Initialise battery
	BulletBattery::initialise(&machine);

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
	Gun* gun = machine.createGun("Test");
	gun->setMemberVariable(Member_X, GUN_X);
	gun->setMemberVariable(Member_Y, GUN_Y);
	gun->setMemberVariable(Member_Angle, 180);

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
	
/*
		// Update player
		if (inFocus())
		{
			oldX = mouseX;
			oldY = mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);

			if (oldX == mouseX && oldY == mouseY)
			{
				float keysX = getHorzMovement();
				float keysY = getVertMovement();
				player.move (keysX * frameTime * 100, keysY * frameTime * 100);
			}
			else
			{
				player.set(mouseX, 600 - mouseY);
			}
		}
*/

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

				// Update bullets
				numBullets = BulletBattery::update(updateFreq);
			}
		}
		else
		{
			curSel = getCurBullet();

			if (lastSel != curSel)
			{
				if (curSel == -1)
				{
					curSel = BulletBattery::getNumBullets() - 1;
					Bullet* b = BulletBattery::getBullet(curSel);
					while (!b->__active)
					{
						curSel--;
						b = BulletBattery::getBullet(curSel);
					}
				}
				else if (curSel == BulletBattery::getNumBullets())
				{
					curSel = 0;
					Bullet* b = BulletBattery::getBullet(curSel);
					while (!b->__active)
					{
						curSel++;
						b = BulletBattery::getBullet(curSel);
					}
				}
				else
				{
					Bullet* b = BulletBattery::getBullet(curSel);
					while (!b->__active)
					{
						curSel++;
						b = BulletBattery::getBullet(curSel);
					}
				}

				if (lastSel >= 0)
				{
					Bullet* b = BulletBattery::getBullet(lastSel);
					b->__selected = false;
				}

				Bullet* b = BulletBattery::getBullet(curSel);
				b->__selected = true;
				std::cout << "bullet:" << std::endl;
				std::cout << "time " << b->__ft->state.suspendTime << std::endl;
				std::cout << "inst " << b->__ft->state.curInstruction << std::endl;
				std::cout << "head " << b->__ft->state.stackHead << std::endl;

				setCurBullet(curSel);
				lastSel = curSel;
			}
		}

		// Render
		renderer.startRendering();

		BulletBattery::render(&renderer);

		renderer.finishRendering();

		if (debugging())
		{
			std::cout << "hello" << std::endl;
		}
	}

	SDL_Quit();
	return 0;
}