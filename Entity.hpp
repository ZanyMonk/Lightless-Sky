#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "SDL2_gfx/SDL2_gfxPrimitives.h"
#include "Utils.hpp"
#include "Engine.hpp"

using namespace std;

class Entity {
protected:
  Engine* E;
public:
  Entity ( Engine* E, Point pos, float size, const string &name = "", Entity* sister = NULL );
  ~Entity ();
  int msg( int type );

  Point pos;
  int seed;
  float size;
  float speed;
  string name;
  Entity* sister;
};

#endif
