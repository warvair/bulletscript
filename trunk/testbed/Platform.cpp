#include "Platform.h"

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
			break;

		default:
			break;
		}
	}

	return true;
}

