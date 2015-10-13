#include <SDL2/SDL.h>
#include <iostream>
#include "Engine.h"

using namespace std;

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::update_display_mode()
{
	SDL_DisplayMode dm;
	SDL_GetDesktopDisplayMode(0, &dm);
	display = dm;
}
