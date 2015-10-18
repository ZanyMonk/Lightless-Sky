#ifndef PLANET_H
#define PLANET_H

#include <SDL2/SDL.h>
#include "Engine.h"
#include "Utils.h"

class Planet
{
public:
	Engine E;
	Point pos;
	Planet( Engine E );
	Planet( Engine E, Point pos );
	~Planet();
	void draw();


private:
};

#endif
