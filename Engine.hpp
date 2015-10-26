#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <iostream>
#include "Utils.hpp"

class Engine
{
public:
	Engine();
	~Engine();
	void update_display_mode();
	// Drawing functions
	void draw_polygon( short int x[], short int y[], int n, int r, int g, int b, int a );

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_DisplayMode display;
	Point cursor;
	int amount;
	bool click;
};

#endif
