#include <SDL2/SDL.h>
#include <cstdio>
#include <iostream>
#include <map>
#include "Engine.h"
#include "Planet.h"
#include "Ship.h"
#include "Game.h"

using namespace std;


int main(int argc, char** argv){
	Engine E;

	// SDL_Window* window1;
	// SDL_Renderer* renderer1;

	int flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		return 1;
	}
	if (SDL_CreateWindowAndRenderer(500, 500, flags, &E.window, &E.renderer)) {
		return 1;
	}
	
	E.update_display_mode();

	Game *game = new Game(E);
	game->start();
	delete game;
	
	return 0;
}
