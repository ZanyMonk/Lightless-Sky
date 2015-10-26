#include "Engine.hpp"

using namespace std;

Engine::Engine()
{
	cursor = Point(0,0);
	amount = 100;
	click = false;
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

void Engine::draw_polygon( short int x[], short int y[], int n, int r, int g, int b, int a )
{
	Sint16 x1 = x[0];
	Sint16 y1 = y[0];
	Sint16 x2, y2;

	for ( int i = 1; i <= n; i++ ) {
		x2 = (i == n ? x[0] : x[i]);
		y2 = (i == n ? y[0] : y[i]);
	  lineRGBA(
	    renderer,
	    x1, y1,
	    x2, y2,
	    r, g, b, a
	  );
		x1 = x[i];
		y1 = y[i];
	}
}
