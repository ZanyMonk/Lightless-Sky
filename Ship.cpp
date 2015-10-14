#include "Ship.h"

using namespace std;

const char SHIP_COLOR_R = 200;
const char SHIP_COLOR_G = 130;
const char SHIP_COLOR_B = 250;

Ship::Ship(Engine E, Planet planet)
:E(E), planet(planet), target(Point()), pos(Point(0,0)), _is_traveling(false) {
	srand(SDL_GetTicks());
	size = 3.0;
	speed = fmod( rand()/1000, 10)+5;
	_health = 100;
	SDL_Delay(1);
}

Ship::~Ship()
{
}

void Ship::draw()
{

	if (
		sin(SDL_GetTicks() / ( 20 * ( 20-speed ) )) > 0
		|| pow( pos.x - planet.pos.x, 2 ) + pow( pos.y - planet.pos.y, 2 )
				> pow( planet.size+ size/2, 2) )
	{
	  filledCircleRGBA(
	    E.renderer,
	    pos.x + 1, pos.y + 1, 3,
			255, 255, 255,
	    fabs( sin(SDL_GetTicks()) / 2.5 ) * 90
	  );

		boxRGBA(
			E.renderer,
			pos.x, pos.y,
			pos.x + 2, pos.y + 2,
			255, 255, 255, 255
		);
	}

}

void Ship::update()
{
	if ( _is_traveling ) {
		// Calcul distance
		double Dist_x = target.x - pos.x ;
		double Dist_y = target.y - pos.y ;

		double Radian = atan2( Dist_y, Dist_x );

		pos.x += cos(Radian) * speed;
		pos.y += sin(Radian) * speed;

		// Test de fin de course
		if (
					( pos.x <= target.x+speed && pos.x > target.x-speed )
			&&	( pos.y <= target.y+speed && pos.y > target.y-speed )
		) {
			_is_traveling = false;
			pos = target;
			attach_point = pos;
		}
	} else {
		gravitate();
	}
}

void Ship::head_to(int x, int y)
{
		target._set(x, y);
		_is_traveling = true;
}

// ----
// Make the ship gravitate around his $attach_point.
void Ship::gravitate()
{
	int step = SDL_GetTicks();
	pos.x = planet.pos.x + cos(step/(20*(20-speed))) * (planet.size*2);
	pos.y = planet.pos.y + (cos(step/(20*(20-speed)))/2 + sin(step/(20*(20-speed)))) * (15);
}
