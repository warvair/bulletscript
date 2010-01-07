#include <cmath>
#include <iostream>
#include <ctime>
#include "bsBulletScript.h"
#include "Main.h"
#include "Platform.h"
#include "RendererGL.h"
#include "BulletSystem.h"
#include "AreaSystem.h"

extern BulletBattery* g_bullets;
extern AreaBattery* g_areas;

using namespace bs;

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
	int runTime = 999999999;
	if (argc >= 2)
		runTime = atoi(argv[1]) * 1000;

	srand(999);

	// Create machine
	Machine machine;

	g_bullets = new BulletBattery(&machine);
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
	machine.registerEmitFunction("area", "ellipse", 2, area_emitEllipse);
	machine.registerEmitFunction("area", "arc", 5, area_emitArc);
	machine.setDieFunction("area", area_kill);
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
	machine.declareMemberVariable("Boss1", "health", 1); // 100%

	std::cout << "Compiling..." << std::endl;

	// Load files
	std::vector<String> scriptFiles = getDirectoryListing(".", "*.script");

	for (size_t i = 0; i < scriptFiles.size(); ++i)
	{
		size_t fileSize;
		uint8* fileBuf = loadFile(scriptFiles[i], fileSize);
		if(machine.compileScript (fileBuf, fileSize) != BS_OK)
		{
			std::cout << "Could not compile " << scriptFiles[i] << std::endl;
			const Log& _log = machine.getLog();

			String msg = _log.getFirstEntry();
			while (msg != Log::END)
			{
				std::cout << msg << std::endl;
				msg = _log.getNextEntry();
			}

			delete[] fileBuf;
			delete g_bullets;
			delete g_areas;
			return 0;
		}

		delete[] fileBuf;
	}

	std::cout << "Initialising..." << std::endl;

#ifndef MINIMAL_APP
	RendererGL renderer;
	if (!renderer.initialise(SCREEN_WIDTH, SCREEN_HEIGHT))
		return 0;

	SDL_ShowCursor(SDL_DISABLE);
#endif

	// Main loop
	unsigned int curTime = getTicks();
	unsigned int totalTime = 0, fpsCounter = 0;
	unsigned int numFrames = 0, updateTime = 0;
	int numBullets = 0;

	// create some objects
	Emitter* emit = machine.createEmitter("AnchorTest", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 180);

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
			float updateMS = (updateTime / (float) numFrames);
			fprintf(stderr, "T: %2.1f update time: %4.3f FPS: %d C: %d\n", totalTime / 1000.0f, updateMS,
				fps, numBullets);
			numFrames = 0;
			updateTime = 0;
		}

		if (emit)
		{
			float xp = emit->getAngle();
			emit->setAngle(xp + 30 * frameTime);

			if (totalTime > 6000)
			{
				machine.destroyEmitter(emit);
				emit = 0;
			}
		}

		// Set script globals - this will update BulletAffector global arguments
		machine.setGlobalVariableValue("Level_Time", totalTime / 1000.0f);

		unsigned int bsTime1 = getTicks();

		// Update machine
		// maybe all emitter/controller/etc update must come after here?
		machine.preUpdate(frameTime);

		// Update types
		numBullets = g_bullets->update(frameTime);
		g_areas->update(frameTime);

		// Update machine again
		machine.postUpdate(frameTime);

		unsigned int bsTime2 = getTicks();
		updateTime += (bsTime2 - bsTime1);

		numFrames++;

		// Render
#ifndef MINIMAL_APP

		renderer.startRendering();

		g_bullets->render(&renderer);
		g_areas->render(&renderer);

		renderer.finishRendering();

#endif
	}

	delete g_bullets;
	delete g_areas;

#ifndef MINIMAL_APP
	SDL_Quit();
#endif
	
	return 0;
}
