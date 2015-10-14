#include "Planet.h"

Planet::Planet(Engine E)
:E(E), pos(Point(50,50)) {
}

Planet::Planet(Engine E, Point pos)
:E(E), pos(pos) {
}

Planet::~Planet() {
}

void Planet::draw()
{
	SDL_Rect skin;
	skin.x = pos.x;
	skin.y = pos.y;
	skin.w = 10;
	skin.h = 10;

	SDL_SetRenderDrawColor(E.renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(E.renderer, &skin);
}
