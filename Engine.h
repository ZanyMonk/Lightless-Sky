#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <iostream>
#include "Utils.h"

class Engine
{
public:
	Engine();
	~Engine();
	void update_display_mode();
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_DisplayMode display;
	Point cursor;
};

#endif
