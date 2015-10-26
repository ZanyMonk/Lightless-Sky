#include <SDL2/SDL.h>
#include <cstdio>
#include <iostream>
#include <map>
#include <stdlib.h>
#include "SDL2_gfx/SDL2_gfxPrimitives.h"
#include "Utils.hpp"
#include "Engine.hpp"
#include "Planet.hpp"
#include "Ship.hpp"
#include "Game.hpp"

using namespace std;

int main(int argc, char** argv){
	Engine* E = new Engine;

	int flags = SDL_WINDOW_BORDERLESS;
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		return 1;
	}

	E->update_display_mode();

	if (SDL_CreateWindowAndRenderer(E->display.w, E->display.h, flags, &E->window, &E->renderer)) {
		return 1;
	}


	Game* game = new Game(E);
	game->start();
	delete game;

	return 0;
}
