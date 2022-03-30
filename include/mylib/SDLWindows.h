#pragma once
#ifndef _SDLWINDOWS_
#define _SDLWINDOWS_
#include "TinyGlm.h"
#include<mutex>
#include<semaphore>
#include"SDL.h"
#include"SDL_revision.h"

class SDLWindows
{
private:
	SDL_Window* myWindow = nullptr;
	SDL_Renderer* myRenderer = nullptr;
	SDL_semaphore* mut;
public:
	
	int k = 0;
	SDLWindows(bool& success, int scene_width, int scene_height);
	virtual ~SDLWindows();

	void Refresh();

	void DrawPixel(int x, int y,TinyGlm::vec4<float> color);
};

#endif //_SDLWINDOWS_

