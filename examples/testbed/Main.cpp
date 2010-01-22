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
	bool fullScreen = false;
	if (argc >= 2)
	{
		if (!strcmp(argv[1], "-f"))
			fullScreen = true;
	}

	std::cout << "BulletScript demo" << std::endl;
	std::cout << "-----------------" << std::endl;
	std::cout << "Arrows:\tmove" << std::endl;
	std::cout << "Z:\tfire" << std::endl;
	std::cout << "Esc:\tquit" << std::endl;
	std::cout << "F1:\ttoggle info" << std::endl;
	std::cout << "F2:\ttoggle rendering" << std::endl;
	std::cout << std::endl;
	std::cout << "Run with -f for fullscreen" << std::endl;
	std::cout << std::endl;




	///////////////////////////////////////////////////////////////////////////
	// Initialise bulletscript
	///////////////////////////////////////////////////////////////////////////
	Machine machine;

	// Register bullet functions
	machine.createType("bullet");

	/*	Emit at an angle (sprite, angle, speed)
	*/
	machine.registerEmitFunction("bullet", "fireA", 3, bullet_emitAngle);
	/*	Emit at a target (sprite, target-x, target-y, angle offset, speed)
	*/
	machine.registerEmitFunction("bullet", "fireT", 5, bullet_emitTarget);
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

	/*	Emit a quad, with origin at its centre (width, height, angle)
	*/
	machine.registerEmitFunction("area", "quadC", 3, area_emitQuadC);
	/*	Emit a quad, with origin at its base (width, height, angle)
	*/
	machine.registerEmitFunction("area", "quadB", 3, area_emitQuadB);
	/*	Emit a quad, with origin at its base, projected a distance away (distance, width, height, angle)
	*/
	machine.registerEmitFunction("area", "quadProj", 4, area_emitQuadProjected);
	/*	Emit an ellipse (radius-x, radius-y)
	*/
	machine.registerEmitFunction("area", "ellipse", 2, area_emitEllipse);
	/*	Emit an arc (radius-x, radius-y, angle-start, angle-end, inner width)
	*/
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
	machine.registerGlobalVariable("BALL", true, 0.0f);					// sprite texture 0
	machine.registerGlobalVariable("COMET", true, 0.5f);				// sprite texture 1
	machine.registerGlobalVariable("Level_Time", true, 0);
	machine.registerGlobalVariable("ScreenSize_X", true, SCREEN_WIDTH);
	machine.registerGlobalVariable("ScreenSize_Y", true, SCREEN_HEIGHT);
	machine.registerGlobalVariable("Player_X", true, 0);
	machine.registerGlobalVariable("Player_Y", true, 0);

	// User member variables must be declared before compiling scripts
//	machine.declareControllerMemberVariable("Boss1", "health", 1); // 100%

	// Compile all script files in directory
	std::cout << "Compiling..." << std::endl;
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
			return 0;
		}

		delete[] fileBuf;
	}




	///////////////////////////////////////////////////////////////////////////
	// Initialise object batteries, renderer and player/bosses
	///////////////////////////////////////////////////////////////////////////
	std::cout << "Initialising..." << std::endl;

	BulletBattery::initialiseTables();
	g_bossBullets = new BulletBattery(&machine);
	g_playerBullets = new BulletBattery(&machine);
	g_areas = new AreaBattery(&machine);

	g_bosses = new BossManager(&machine);
	Player* player = new Player(&machine);

	RendererGL renderer;
	if (!renderer.initialise(SCREEN_WIDTH, SCREEN_HEIGHT, fullScreen))
		return 0;

	// Load images now that renderer is created
	player->setImage("player.tga");
	g_bosses->loadImages();




	///////////////////////////////////////////////////////////////////////////
	// Main loop
	///////////////////////////////////////////////////////////////////////////
	unsigned int totalTime = 0, fpsCounter = 0;
	unsigned int numFrames = 0, updateTime = 0;
	int numBullets = 0;

	bool showInfo = true, doRender = true;

	unsigned int curTime = getTicks();
	while (true)
	{
		// Get update time
		unsigned int newTime = getTicks();
		unsigned int deltaTime = newTime - curTime;

		curTime = newTime;
		totalTime += deltaTime;
		fpsCounter += deltaTime;

		float frameTime = deltaTime / 1000.0f;

		// Debugging/info
		char fpsString[80];
		if (fpsCounter > 1000)
		{
			fpsCounter -= 1000;

			int fps = numFrames;
			float updateMS = (updateTime / (float) numFrames);

			sprintf(fpsString, "%4.3fms, %d FPS, %d bullets\n", updateMS, fps, numBullets);
			numFrames = 0;
			updateTime = 0;
		}




		/// Input
		if (!processMessages())
			break;

		if (keyPressed(SDLK_F1))
			showInfo = !showInfo;

		if (keyPressed(SDLK_F2))
			doRender = !doRender;




		// Player and boss logic
		player->doInput(frameTime);
		g_bosses->update(frameTime);
		machine.setGlobalVariableValue("Level_Time", totalTime / 1000.0f);
		machine.setGlobalVariableValue("Player_X", player->getX());
		machine.setGlobalVariableValue("Player_Y", player->getY());




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
		renderer.startRendering();

		if (doRender)
		{
			g_bossBullets->render(&renderer);
			g_playerBullets->render(&renderer);
			g_areas->render(&renderer);
			
			// Upload quads so they are rendered behind units
			renderer._renderQuadBatch();
			
			g_bosses->render();
			player->render();
		}

		if (showInfo)
			renderer.print (5, SCREEN_HEIGHT - 20, fpsString);

		renderer.finishRendering();
	}

	///////////////////////////////////////////////////////////////////////////
	// Main loop
	///////////////////////////////////////////////////////////////////////////
	delete g_bossBullets;
	delete g_playerBullets;
	delete g_areas;
	delete g_bosses;
	delete player;

	SDL_Quit();
	
	return 0;
}
