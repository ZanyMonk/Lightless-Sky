#ifndef PLANET_H
#define PLANET_H

#include <iostream>
#include <array>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "SDL2_gfx/SDL2_gfxPrimitives.h"
#include "Engine.hpp"
#include "Utils.hpp"

using namespace std;

const int HOVER_GLOW_ALPHA = 15;

class Planet
{
public:

	Planet( Engine* E );
	Planet( Engine* E, Point position, float size, string name = "" );
	Planet( Engine* E, int x, int y, float size, string name = "" );
	~Planet();
	void draw();
	void draw_glow();
	string generate_name();

	Engine* E;
	Point pos;
	string name;
	int seed;
	float size;
	int hover;
	int focus;
private:
};

#endif
