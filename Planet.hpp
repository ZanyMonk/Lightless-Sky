#ifndef PLANET_H
#define PLANET_H

#include <iostream>
#include <array>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL2_gfx/SDL2_gfxPrimitives.h"
#include "Utils.hpp"
#include "Engine.hpp"
#include "Faction.hpp"
#include "Entity.hpp"
#include "Ship.hpp"

using namespace std;

const int HOVER_GLOW_ALPHA = 15;
const int LINK_GLOW_WIDTH = 15;

class Planet : public Entity
{
public:
	Planet( Engine* E, Faction* faction, Point pos, float size, const string &name = "", Planet* sister = NULL );
	~Planet();

	// Fonctions natives (Entity)
	void update();
	void draw();

	// Texturage
	SDL_Texture* generate_text_relief();

	// Dessin
	void draw_planet();
	void draw_link( Point* pos1 = nullptr, Point* pos2 = nullptr, Uint8 r = 255, Uint8 g = 255, Uint8 b = 255 );
	void draw_glow();
	void draw_shadow();

	// Gestion
	void link_to( Planet* new_sister );
	int send( int n, Planet* target );

	// Divers
	string generate_name( Uint8 min, Uint8 max );

	Planet* sister;
	int hover;
	int focus;
	int select;
	SDL_Texture* text_relief;
	SDL_Texture* text_name;
	vector<Planet*> planets;
	vector<Ship*> ships;
private:
};

#endif
