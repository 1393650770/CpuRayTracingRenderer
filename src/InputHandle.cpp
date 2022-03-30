#include "InputHandle.h"
#include <SDL.h>


void InputHandle::ListenInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type) {

		case SDL_QUIT:
			is_runing = false;
			break;
		default:
			break;
		}
	}
}
