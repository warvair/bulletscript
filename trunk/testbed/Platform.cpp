#include "Platform.h"

static float gHorz = 0;
static float gVert = 0;

static float gCount = 1;

static bool gInFocus = true;

static bool gDebug = false;

static bool gPaused = false;

static int gCurBullet = -1;

#ifdef MINIMAL_APP
bool processMessages()
{
	return true;
}
#else
bool processMessages()
{
	SDL_Event evt;
	while (SDL_PollEvent(&evt)) 
	{
		switch (evt.type) 
		{
		case SDL_QUIT:
			return false;

		case SDL_KEYDOWN:
			if (evt.key.keysym.sym == SDLK_ESCAPE)
				return false;
			else if(evt.key.keysym.sym == SDLK_UP)
			{
				gCurBullet++;
			}
			else if(evt.key.keysym.sym == SDLK_DOWN)
			{
				gCurBullet--;
				if (gCurBullet < 0)
					gCurBullet = -1;
			}
			else if(evt.key.keysym.sym == SDLK_w)
				gCount += 1;
			else if(evt.key.keysym.sym == SDLK_q)
			{
				gCount -= 1;
				if (gCount < 1)
					gCount = 1;
			}
			else if (evt.key.keysym.sym == SDLK_d)
				gDebug = !gDebug;
			else if (evt.key.keysym.sym == SDLK_p)
				gPaused = !gPaused;
			break;

		case SDL_KEYUP:
			if(evt.key.keysym.sym == SDLK_LEFT)
				gHorz = 0;
			else if(evt.key.keysym.sym == SDLK_RIGHT)
				gHorz = 0;
			else if(evt.key.keysym.sym == SDLK_UP)
				gVert = 0;
			else if(evt.key.keysym.sym == SDLK_DOWN)
				gVert = 0;
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