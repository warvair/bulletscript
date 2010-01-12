#include <cmath>
#include <iostream>
#include <ctime>
#include "bsBulletScript.h"
#include "Main.h"
#include "Platform.h"
#include "RendererGL.h"
#include "BulletSystem.h"
#include "AreaSystem.h"
#include "Player.h"
#include "Boss.h"

extern BulletBattery* g_bossBullets, *g_playerBullets;
extern AreaBattery* g_areas;

BossManager* g_bosses = 0;

using namespace bs;

int main (int argc, char **argv)
{
	int runTime = 999999999;
	if (argc >= 2)
		runTime = atoi(argv[1]) * 1000;

	srand(999);

	// Create machine
	Machine machine;

	BulletBattery::initialiseTables();
	g_bossBullets = new BulletBattery(&machine);
	g_playerBullets = new BulletBattery(&machine);
	g_areas = new AreaBattery(&machine);

	// Register bullet functions
	machine.createType("bullet");

	machine.registerEmitFunction("bullet", "fireA", 2, bullet_emitAngle);
	machine.registerEmitFunction("bullet", "fireT", 4, bullet_emitTarget);
	machine.setDieFunction("bullet", bullet_kill);

	machine.setAnchorX("bullet", bullet_setX, bullet_getX);
	machine.setAnchorY("bullet", bullet_setY, bullet_getY);
	machine.setAnchorAngle("bullet", bullet_setAngle, bullet_getAngle);
	machine.registerProperty("bullet", "speed",	bullet_setSpeed, bullet_getSpeed);
	machine.registerProperty("bullet", "red", bullet_setRed, bullet_getRed);
	machine.registerProperty("bullet", "green",	bullet_setGreen, bullet_getGreen);
	machine.registerProperty("bullet", "blue", bullet_setBlue, bullet_getBlue);
	machine.registerProperty("bullet", "alpha",	bullet_setAlpha, bullet_getAlpha);
	machine.registerAffector("bullet", "Gravity", bullet_gravity);

	// Register area functions
	machine.createType("area");

	machine.registerEmitFunction("area", "quadC", 3, area_emitQuadC);
	machine.registerEmitFunction("area", "quadB", 3, area_emitQuadB);
	machine.registerEmitFunction("area", "quadProj", 4, area_emitQuadProjected);
	machine.registerEmitFunction("area", "ellipse", 2, area_emitEllipse);
	machine.registerEmitFunction("area", "arc", 5, area_emitArc);
	machine.setDieFunction("area", area_kill);

	machine.setAnchorX("area", area_setX, area_getX);
	machine.setAnchorY("area", area_setY, area_getY);
	machine.setAnchorAngle("area", area_setAngle, area_getAngle);

	machine.registerProperty("area", "alpha", area_setAlpha, area_getAlpha);
	machine.registerProperty("area", "width", area_setWidth, area_getWidth);
	machine.registerProperty("area", "height", area_setHeight, area_getHeight);
	machine.registerProperty("area", "iwidth", area_setInnerWidth, area_getInnerWidth);
	machine.registerProperty("area", "iheight",	area_setInnerHeight, area_getInnerHeight);
	machine.registerProperty("area", "start", area_setStart, area_getStart);
	machine.registerProperty("area", "end", area_setEnd, area_getEnd);

	// Register global variables
	machine.registerGlobalVariable("Level_Time", true, 0);
	machine.registerGlobalVariable("ScreenSize_X", true, SCREEN_WIDTH);
	machine.registerGlobalVariable("ScreenSize_Y", true, SCREEN_HEIGHT);
	machine.registerGlobalVariable("Test_Global", false, 0);

	// User member variables must be declared before compiling scripts
	machine.declareControllerMemberVariable("Boss1", "health", 1); // 100%

	std::cout << "Compiling..." << std::endl;

	// Load files
	std::vector<std::string> scriptFiles = getDirectoryListing(".", "*.script");

	for (size_t i = 0; i < scriptFiles.size(); ++i)
	{
		size_t fileSize;
		unsigned char* fileBuf = loadFile(scriptFiles[i].c_str(), fileSize);
		if(machine.compileScript (fileBuf, fileSize) != BS_OK)
		{
			std::cout << "Could not compile " << scriptFiles[i] << std::endl;
			const Log& _log = machine.getLog();

			std::string msg = _log.getFirstEntry();
			while (msg != Log::END)
			{
				std::cout << msg << std::endl;
				msg = _log.getNextEntry();
			}

			delete[] fileBuf;
			delete g_bossBullets;
			delete g_playerBullets;
			delete g_areas;
			return 0;
		}

		delete[] fileBuf;
	}

	std::cout << "Initialising..." << std::endl;

	// Create player and g_bosses
	g_bosses = new BossManager(&machine);
	Player* player = new Player(&machine);

#ifndef MINIMAL_APP
	RendererGL renderer;
	if (!renderer.initialise(SCREEN_WIDTH, SCREEN_HEIGHT))
		return 0;

	SDL_ShowCursor(SDL_DISABLE);

	// Player/Bosses
	player->setImage("player.tga");
	g_bosses->loadImages();
	player->setGuns("PlayerController");
	
#endif

	// Main loop
	unsigned int curTime = getTicks();
	unsigned int totalTime = 0, fpsCounter = 0;
	unsigned int numFrames = 0, updateTime = 0;
	int numBullets = 0;

	while (true)
	{
		// Get update time
		unsigned int newTime = getTicks();
		unsigned int deltaTime = newTime - curTime;

		curTime = newTime;
		totalTime += deltaTime;
		fpsCounter += deltaTime;

		float frameTime = deltaTime / 1000.0f;

#ifndef MINIMAL_APP
		if (!processMessages())
			break;

		// Move player
		player->doInput(frameTime);

#endif

		if (fpsCounter > 1000)
		{
			fpsCounter -= 1000;

			int fps = numFrames;
			float updateMS = (updateTime / (float) numFrames);
			fprintf(stderr, "%4.3fms, %d FPS, %d bullets\n", updateMS, fps, numBullets);
			numFrames = 0;
			updateTime = 0;
		}

		// Do all changes to system here, before we update the machine
		g_bosses->update(frameTime);
		machine.setGlobalVariableValue("Level_Time", totalTime / 1000.0f);

		// Update bulletscript
		unsigned int bsTime1 = getTicks();
		machine.preUpdate(frameTime);

		numBullets = g_bossBullets->update(frameTime);
		numBullets += g_playerBullets->update(frameTime);
		g_areas->update(frameTime);

		machine.postUpdate(frameTime);

		updateTime += (getTicks() - bsTime1);
		numFrames++;

		// Render
#ifndef MINIMAL_APP
		renderer.startRendering();

		g_bossBullets->render(&renderer);
		g_playerBullets->render(&renderer);
		g_areas->render(&renderer);
		g_bosses->render();
		player->render();

		renderer.finishRendering();
#endif
	}

	delete g_bossBullets;
	delete g_playerBullets;
	delete g_areas;
	delete g_bosses;
	delete player;

#ifndef MINIMAL_APP
	SDL_Quit();
#endif
	
	return 0;
}
