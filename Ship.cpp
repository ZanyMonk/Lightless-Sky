#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "SDL2_gfxPrimitives.h"
#include "Ship.h"

using namespace std;

const char SHIP_COLOR_R = 200;
const char SHIP_COLOR_G = 130;
const char SHIP_COLOR_B = 250;

Ship::Ship(Engine E)
:E(E), target_x(0), target_y(0), x(0), y(0), _is_traveling(false) {
	srand(SDL_GetTicks());
	this->_faction = 0;
	this->size = 10;
	this->_health = 100;
	this->speed = (rand()%9000)/1000.00+2;
	SDL_Delay(400);
}

Ship::~Ship()
{
}

void Ship::draw()
{
	SDL_Rect skin;
	skin.x = x;
	skin.y = y;
	skin.w = 3;
	skin.h = 3;

	SDL_SetRenderDrawColor(E.renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(E.renderer, &skin);
}

<<<<<<< HEAD
void Ship::update()
{
	if ( _is_traveling ) {
		// Calcul distance
		double Dist_x = target_x - x ;
		double Dist_y = target_y - y ;

		double Radian = atan2( Dist_y, Dist_x );

		this->x += cos(Radian) * speed;
		this->y += sin(Radian) * speed;

		// Test de fin de course
		if (
					( x <= target_x+speed && x > target_x-speed )
			&&	( y <= target_y+speed && y > target_y-speed )
		) {
			this->_is_traveling = false;
			this->x = target_x;
			this->y = target_y;
		}
	} else {
		gravitate();
	}
}

void Ship::head_to(int x, int y)
{
		this->_is_traveling = true;
		this->target_x = x;
		this->target_y = y;
}

// ----
// Make the ship gravitate around his $attach_point.
void Ship::gravitate()
=======
void Ship::move_to(int target_x, int target_y)
>>>>>>> fc98453b2e7a21d0323b773cd4bf0e6ab14b9dfb
{
		//calcul distance

		_is_traveling = 1;

		if (_is_traveling) {

		double Dist_x = (target_x)-(x) ;
		double Dist_y = (target_y)-(y) ;

		double Radian = atan2(Dist_y,Dist_x);

		x += (cos(Radian)*SHIP_SPEED);
		y += (sin(Radian)*SHIP_SPEED);

		//Test fin de course
		if ( ( x <= target_x+10 && x > target_x-10 ) && ( y <= target_y+10 && y > target_y-10 ) )  {

			_is_traveling = 0;
			x=target_x;
			y=target_y;
			}
	}
}

int Ship::get_faction()
{
	return this->_faction;
}

bool Ship::is_traveling()
{
	return this->_is_traveling;
}
