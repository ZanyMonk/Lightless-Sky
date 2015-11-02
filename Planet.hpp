#ifndef PLANET_H
#define PLANET_H

#include <iostream>
#include <array>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "SDL2_gfx/SDL2_gfxPrimitives.h"
#include "Utils.hpp"
#include "Engine.hpp"
#include "Entity.hpp"
#include "Ship.hpp"

using namespace std;

const int HOVER_GLOW_ALPHA = 15;
const int LINK_GLOW_WIDTH = 15;

class Planet : public Entity
{
public:
	Planet( Engine* E, Point pos, float size, const string &name = "" );
	~Planet();
	void onMouseDown( SDL_Event* evt );
	void onMouseUp( SDL_Event* evt );
	void update();
	void draw();
	void draw_planet();
	void draw_link();
	void draw_glow();
	void draw_shadow();
	int send( int n, Planet* target );
	int host( Ship* ship );
	int msg( int type );
	string generate_name( Uint8 min, Uint8 max );

	int seed;
	int hover;
	int focus;
	int select;
	SDL_Texture* text_name;
	vector<Planet*> planets;
	vector<Ship*> ships;
private:
};

#endif
