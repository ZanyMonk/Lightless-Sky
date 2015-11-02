#ifndef SHIP_H

#define SHIP_H
#define _USE_MATH_DEFINES

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "SDL2_gfx/SDL2_gfxPrimitives.h"
#include "Engine.hpp"
#include "Utils.hpp"
#include "Entity.hpp"

class Ship : public Entity
{
public:
	Ship( Engine* E, Entity* planet );
	~Ship();
	void draw();
	void update();
	void head_to( Entity* new_planet );
	void go_to_target();
	void gravitate();

	Entity* planet;
	Point target;
	int seed;
	bool is_traveling;
private:
	int _health;
};

#endif
