#include "Ship.hpp"

using namespace std;

const char SHIP_COLOR_R = 200;
const char SHIP_COLOR_G = 130;
const char SHIP_COLOR_B = 250;

Ship::Ship( Engine* E, Entity* planet )
	:Entity(E, planet->pos, 1.0),
	planet(planet),
	target(planet->pos),
	is_traveling(false)
{
	seed = SDL_GetTicks();
	srand(seed);
	seed = rand();
	_health = 100;
	SDL_Delay(1);
}

Ship::~Ship()
{
}

//----
// Dessine le vaisseau
void Ship::draw()
{

	if (
		is_traveling
		|| (
			// On cache le vaisseau si il se trouve derrière la planète
			sin((SDL_GetTicks()-seed%1000) / ( 20 * ( 20-speed/1.5 ) )) > 0
			|| pow( pos.x - planet->pos.x, 2 ) + pow( pos.y - planet->pos.y, 2 )
				> pow( planet->size + size/2, 2)
		)
	) {
		// On peut carrément améliorer ça, soit avec un sprite, soit avec un peu de code ;)
		double r = size*3.0;
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

//----
// Met à jour la position du vaisseau
void Ship::update()
{
	if ( is_traveling ) {
		go_to_target();
	} else {
		// Si on est sur une planète émétrice, on bouge vers la planète réceptrice
		if ( planet->sister != NULL ) {
			// planet->msg(0);
			head_to(planet->sister);
			return;
		}
		gravitate();
	}
}

//----
// Sélectionne un nouveau cap
// Arguments :
//	Entity* new_planet		Planète cible
void Ship::head_to(Entity* new_planet)
{
		target._set(new_planet->pos.x, new_planet->pos.y);
		planet = new_planet;
		is_traveling = true;
}

//----
// Calcule les nouvelles coordonnées de la trajectoire vers target
void Ship::go_to_target()
{
	// Recalcul du point d'arrivée
	int step = SDL_GetTicks()-seed%10000;
	float S = sin(step/((20-seed%5)*(20-speed/1.5)))*2;
	float C = cos(step/(20*(20-speed/1.5)));

	target.x = planet->pos.x + C * (planet->size*2+S*10);
	target.y = planet->pos.y + int(((C+0.1)/2 + (S+0.1)/10) * (15+seed%int(planet->size*2)));

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
		is_traveling = false;
		pos._set(target.x, target.y);
	}
}

// ----
// Le vaisseau gravite autour de sa planète
void Ship::gravitate()
{
	int step = SDL_GetTicks()-seed%10000;
	float S = sin(step/((20-seed%5)*(20-speed/1.5)))*2;
	float C = cos(step/(20*(20-speed/1.5)));
	pos.x = planet->pos.x + C * (planet->size*2+S*10);
	pos.y = planet->pos.y + int(((C+0.1)/2 + (S+0.1)/10) * (15+seed%int(planet->size*2)));
}
