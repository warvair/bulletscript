#include "Platform.h"

static float gHorz = 0.0f;
static float gVert = 0.0f;

static float gCount = 1.0f;

static bool gInFocus = true;

void toggleGun(int index);

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
			else if(evt.key.keysym.sym >= SDLK_1 && evt.key.keysym.sym <= SDLK_5)
				toggleGun(evt.key.keysym.sym - SDLK_1);
			else if(evt.key.keysym.sym == SDLK_LEFT)
				gHorz = -1.0f;
			else if(evt.key.keysym.sym == SDLK_RIGHT)
				gHorz = 1.0f;
			else if(evt.key.keysym.sym == SDLK_UP)
				gVert = 1.0f;
			else if(evt.key.keysym.sym == SDLK_DOWN)
				gVert = -1.0f;
			else if(evt.key.keysym.sym == SDLK_w)
				gCount += 1.0f;
			else if(evt.key.keysym.sym == SDLK_q)
			{
				gCount -= 1.0f;
				if (gCount < 1.0f)
					gCount = 1.0f;
			}
			break;

		case SDL_KEYUP:
			if(evt.key.keysym.sym == SDLK_LEFT)
				gHorz = 0.0f;
			else if(evt.key.keysym.sym == SDLK_RIGHT)
				gHorz = 0.0f;
			else if(evt.key.keysym.sym == SDLK_UP)
				gVert = 0.0f;
			else if(evt.key.keysym.sym == SDLK_DOWN)
				gVert = 0.0f;
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