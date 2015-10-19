#ifndef PLANET_H
#define PLANET_H

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "SDL2_gfxPrimitives.h"
#include "Engine.h"
#include "Utils.h"

using namespace std;

class Planet
{
public:
	Planet( Engine* E );
	Planet( Engine* E, int x, int y, float size );
	Planet( Engine* E, Point position, float size );
	~Planet();
	void draw();
	void draw_glow();
	void draw_options();

	Engine* E;
	Point pos;
	float size;
	int hover;
	int focus;
private:
};

#endif
