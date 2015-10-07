#include <SDL2/SDL.h>
#include "Ship.h"

const int SHIP_SPEED = 1;
const char SHIP_COLOR_R = 255;
const char SHIP_COLOR_G = 0;
const char SHIP_COLOR_B = 0;

Ship::Ship(Engine E)
:E(E), dep_x(0), dep_y(0), x(0), y(0), _is_traveling(true) {
	this->_faction = 0;
	this->size = 2;
	this->_health = 100;
}

Ship::~Ship()
{
}


void Ship::draw()
{
	SDL_Rect skin;

	skin.x = x;
	skin.y = y;
	skin.w = this->size;
	skin.h = this->size;
	
	SDL_SetRenderDrawColor(E.renderer, SHIP_COLOR_R, SHIP_COLOR_G, SHIP_COLOR_B, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(E.renderer, &skin);
}

void Ship::move_to(int x, int y)
{

}

int Ship::get_faction()
{
	return this->_faction;
}

bool Ship::is_traveling()
{
	return this->_is_traveling;
}
