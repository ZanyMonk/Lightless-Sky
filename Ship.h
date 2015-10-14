#ifndef SHIP_H

#define SHIP_H
#define _USE_MATH_DEFINES

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "SDL2_gfxPrimitives.h"
#include "Engine.h"
#include "Utils.h"

class Ship
{
public:
	Ship( Engine E );
	~Ship();
	void draw();
	void update();
	void head_to(int x, int y);
	void gravitate();
	Engine E;
	Point target;
	Point pos;
	Point attach_point;
	int size;
	double speed;
	bool _is_traveling;
private:
	int _health;
};

#endif
