#include "Engine.h"

using namespace std;

Engine::Engine()
{
	cursor = Point(0,0);
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
