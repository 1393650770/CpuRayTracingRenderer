#include "SDLWindows.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;//注意__FILE__是双下划线
#endif 

SDLWindows::SDLWindows(bool& success,int scene_width,int scene_height)
{
	mut = SDL_CreateSemaphore(1);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		myWindow = SDL_CreateWindow("MyCpuRaytracing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, scene_width, scene_height, SDL_WINDOW_SHOWN);
		if (myWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			myRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_SOFTWARE);
			if (myRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
		}
	}
	k= scene_width;
}

SDLWindows::~SDLWindows()
{
	//Destroy window    
	SDL_DestroyRenderer(myRenderer);
	SDL_DestroyWindow(myWindow);
	SDL_DestroySemaphore(mut);
	//SDL_DestroyTexture(gTexture);
	myWindow = NULL;
	myRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();

}

void SDLWindows::Refresh()
{
	SDL_RenderPresent(myRenderer);
}

void SDLWindows::DrawPixel(int x, int y, TinyGlm::vec4<float> color)
{
	SDL_SemWait(mut);
	SDL_SetRenderDrawColor(myRenderer, int(color.x*255), int(color.y * 255), int(color.z * 255), int(color.w * 255));
	SDL_RenderDrawPoint(myRenderer, x,  y);
	SDL_SemPost(mut);
}
