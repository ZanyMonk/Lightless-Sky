#include "Ship.h"

using namespace std;

const char SHIP_COLOR_R = 200;
const char SHIP_COLOR_G = 130;
const char SHIP_COLOR_B = 250;

Ship::Ship(Engine E)
:E(E), target(Point()), pos(Point(0,0)), attach_point(Point(500,500)), _is_traveling(false) {
	srand(SDL_GetTicks());
	size = 10;
	speed = rand()%10+5;
	_health = 100;
	SDL_Delay(1);
}

Ship::~Ship()
{
}

void Ship::draw()
{
	SDL_Rect skin;
	skin.x = pos.x;
	skin.y = pos.y;
	skin.w = 3;
	skin.h = 3;

	SDL_SetRenderDrawColor(E.renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(E.renderer, &skin);
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
	// cout << (cos(step/40)*50) << endl;
	pos.x = attach_point.x + (sin(step/(20*speed))-cos(step/(20*speed))) * (50);
	pos.y = attach_point.y + (cos(step/(20*speed))-sin(step/(20*speed))*4) * (15);
}
