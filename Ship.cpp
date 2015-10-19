#include "Ship.h"

using namespace std;

const char SHIP_COLOR_R = 200;
const char SHIP_COLOR_G = 130;
const char SHIP_COLOR_B = 250;

Ship::Ship(Engine* E, Planet planet)
:E(E), planet(planet), target(Point()), pos(Point(0,0)), _is_traveling(false) {
	seed = SDL_GetTicks();
	srand(seed);
	seed = rand();
	size = 1.0;
	speed = 3;
	_health = 100;
	SDL_Delay(1);
}

Ship::~Ship()
{
}

void Ship::draw()
{

	// We hide the ship if it is behind the planet
	if (
		_is_traveling
		|| (
			sin((SDL_GetTicks()-seed%1000) / ( 20 * ( 20-speed/1.5 ) )) > 0
			|| pow( pos.x - planet.pos.x, 2 ) + pow( pos.y - planet.pos.y, 2 )
					> pow( planet.size + size/2, 2)
		)
	) {
		double r = 3.0;
	  filledCircleRGBA(
	    E->renderer,
	    pos.x + r/2, pos.y + r/2, r,
			255, 255, 255,
	    fabs( sin(SDL_GetTicks()) / 2.5 ) * 90
	  );

		boxRGBA(
			E->renderer,
			pos.x, pos.y,
			pos.x + size, pos.y + size,
			255, 255, 255, 255
		);
	}

}

void Ship::update()
{
	if ( _is_traveling ) {
		// Recalcul du point d'arrivée
		int step = SDL_GetTicks()-seed%1000;
		float S = sin((step-seed%1000)/((20-seed%5)*(20-speed/1.5)))*2;
		float C = cos(step/(20*(20-speed/1.5)));
		target.x = planet.pos.x + C * (planet.size*2+S*10);
		target.y = planet.pos.y + (C/2 + S/10) * (15+seed%int(planet.size*2));

		// Calcul distance
		double Dist_x = target.x - pos.x ;
		double Dist_y = target.y - pos.y ;

		double Radian = atan2( Dist_y, Dist_x );

		pos.x += cos(Radian) * speed;
		pos.y += sin(Radian) * speed;

		// Test de fin de course
		if (
					( pos.x <= target.x+speed/2 && pos.x > target.x-speed/2 )
			&&	( pos.y <= target.y+speed/2 && pos.y > target.y-speed/2 )
		) {
			_is_traveling = false;
			pos = target;
			attach_point = pos;
		}
	} else {
		gravitate();
	}
}

// Sélectionne un nouveau cap
void Ship::head_to(Planet new_planet)
{
		target._set(new_planet.pos.x, new_planet.pos.y);
		planet = new_planet;
		_is_traveling = true;
}

// ----
// Le vaisseau gravite autour de sa planète
void Ship::gravitate()
{
	int step = SDL_GetTicks()-seed%1000;
	float S = sin((step-seed%1000)/((20-seed%5)*(20-speed/1.5)))*2;
	float C = cos(step/(20*(20-speed/1.5)));
	pos.x = planet.pos.x + C * (planet.size*2+S*10);
	pos.y = planet.pos.y + (C/2 + S/10) * (15+seed%int(planet.size*2));
}
