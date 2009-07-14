#include <iostream>
#include "shScriptMachine.h"
#include "shBulletMachine.h"
#include "shGun.h"
#include "Platform.h"
#include "RendererGL.h"
#include "BulletSystem.h"
#include "Ship.h"

#if SHMUPPET_PLATFORM == SHMUPPET_PLATFORM_WIN32
#	include <windows.h>
#endif

using namespace Shmuppet;

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

// Error callback function for ScriptMachine
void script_err(const char* msg)
{
	std::cerr << msg << std::endl;
}

static Ship *gShip = 0;

// Cycle gun on ship
void toggleGun(int index)
{
	gShip->toggleGun(index);
}

int main (int argc, char **argv)
{
	BulletMachine<Bullet> bm;
	bm.registerAffectorFunction("Force", BulletAffector_Force);
	bm.registerAffectorFunction("Home", BulletAffector_Home);
	bm.registerAffectorFunction("DelayAccel", BulletAffector_DelayAccel);
	bm.registerAffectorFunction("Explode", BulletAffector_Explode);

	ScriptMachine sm(script_err, &bm);
	sm.registerFireFunction("fireA", BulletBattery::emitAngle);
	sm.registerFireFunction("fireT", BulletBattery::emitTarget);
	sm.registerGlobalVariable("Player_X", 400);
	sm.registerGlobalVariable("Player_Y", 32);
	sm.registerGlobalVariable("Level_Time", 0.0f);
	sm.registerGlobalVariable("ScreenSize_X", 800.0f);
	sm.registerGlobalVariable("ScreenSize_Y", 600.0f);

	// Load file
	size_t fileSize;
	uint8* fileBuf = loadFile("Guns.script", fileSize);
	if(sm.compileScript (fileBuf, fileSize) != 0)
	{
		delete[] fileBuf;
		return 0;
	}

	delete[] fileBuf;

	// Initialise battery
	BulletBattery::initialise();

	// Renderer
	RendererGL renderer;
	if (!renderer.initialise(800, 600))
		return 0;

	SDL_ShowCursor(SDL_DISABLE);

	// Create a test ship
	gShip = new Ship("ship1.tga", 400, 550, &sm, &bm);
	gShip->addGun("Tracker", 0, -28);
	gShip->addGun("Homer", 20, 5);
	gShip->addGun("Swarm", -20, 5);
	gShip->addGun("SideSpray", 12, -16);
	gShip->addGun("ClusterBomb", -12, -16);

	Ship ship2("ship1.tga", 600, 450, &sm, &bm);
	ship2.addGun("Tracker", 0, -28);
	ship2.addGun("Homer", 20, 5);
	ship2.addGun("Swarm", -20, 5);
	ship2.addGun("SideSpray", 12, -16);
	ship2.addGun("ClusterBomb", -12, -16);

	Ship player("player.tga", 400, 32, &sm, &bm);

	// Print interface commands
	std::cout << "Shmuppet BulletScript" << std::endl;
	std::cout << "---------------------" << std::endl;
	std::cout << "[1-5] Toggle bullet emitters." << std::endl;
	std::cout << "[Esc] Quit." << std::endl;
	std::cout << "[Mouse] Move ship." << std::endl;

	// Main loop
	unsigned int curTime = SDL_GetTicks();
	unsigned int totalTime = 0;

	unsigned int fpsCounter = 0;
	unsigned int numFrames = 0;

	int numBullets = 0;

	while (true)
	{
		if (!processMessages())
			break;

		int mouseRelX, mouseRelY;
		SDL_GetRelativeMouseState(&mouseRelX, &mouseRelY);

		// Get update time
		unsigned int newTime = SDL_GetTicks();
		unsigned int deltaTime = newTime - curTime;
		curTime = newTime;
		numFrames++;
		
		totalTime += deltaTime;
		fpsCounter += deltaTime;
		if (fpsCounter > 1000)
		{
			fpsCounter -= 1000;
			std::cerr << "FPS: " << numFrames << " Bullets: " << numBullets << std::endl;
			numFrames = 0;
		}

		float frameTime = deltaTime / 1000.0f;

		// Set script globals - this will update BulletAffector global arguments
		sm.setGlobalVariableValue("Level_Time", totalTime / 1000.0f);
		sm.setGlobalVariableValue("Player_X", player.getX());
		sm.setGlobalVariableValue("Player_Y", player.getY());
	
		// Update BulletAffector function arguments
		bm.updateBulletAffectors();

		// Update ships
		player.move (mouseRelX, 0);

		gShip->updateGuns(frameTime);
		ship2.updateGuns(frameTime);
		
		// Update bullets
		numBullets = BulletBattery::update(frameTime, &bm);

		// Render
		renderer.startRendering();

		player.render(&renderer);
		gShip->render(&renderer);
		ship2.render(&renderer);
		BulletBattery::render(&renderer);

		renderer.finishRendering();
	}

	SDL_Quit();
	delete gShip;
	return 0;
}