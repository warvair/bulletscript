#include "Platform.h"

static float gHorz = 0;
static float gVert = 0;

static float gCount = 1;

static bool gInFocus = true;

static bool gDebug = false;

static bool gPaused = false;

static int gCurBullet = -1;

static int gKeys[SDLK_LAST];

#ifdef MINIMAL_APP
bool processMessages()
{
	return true;
}
#else
bool processMessages()
{
	// Only check for key presses
	memset(gKeys, 0, SDLK_LAST * sizeof(int));

	SDL_Event evt;
	while (SDL_PollEvent(&evt)) 
	{
		switch (evt.type) 
		{
		case SDL_QUIT:
			return false;

		case SDL_KEYDOWN:
			gKeys[evt.key.keysym.sym] = 1;
			if (evt.key.keysym.sym == SDLK_ESCAPE)
				return false;

		case SDL_KEYUP:
			break;

		case SDL_ACTIVEEVENT:
			if (evt.active.state == SDL_APPMOUSEFOCUS)
			{
				if (evt.active.gain == 0)
				{
					gInFocus = false;
				}
				else if (evt.active.gain == 1)
				{
					gInFocus = true;
				}
			}
			break;

		default:
			break;
		}
	}

	return true;
}
#endif

bool keyDown(int key)
{
	return (gKeys[key] == 1);
}

float getHorzMovement()
{
	return gHorz;
}

float getVertMovement()
{
	return gVert;
}

float getBulletCount()
{
	return gCount;
}

bool inFocus()
{
	return gInFocus;
}

bool debugging()
{
	return gDebug;
}

bool paused()
{
	return gPaused;
}

int getCurBullet()
{
	return gCurBullet;
}

void setCurBullet(int val)
{
	gCurBullet = val;
}