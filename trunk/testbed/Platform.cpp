#include "Platform.h"

static float gSideways = 0.0f;

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
				gSideways = -1.0f;
			else if(evt.key.keysym.sym == SDLK_RIGHT)
				gSideways = 1.0f;
			break;

		case SDL_KEYUP:
			if(evt.key.keysym.sym == SDLK_LEFT)
				gSideways = 0.0f;
			else if(evt.key.keysym.sym == SDLK_RIGHT)
				gSideways = 0.0f;
			break;

		default:
			break;
		}
	}

	return true;
}

float getSidewaysMovement()
{
	return gSideways;
}

