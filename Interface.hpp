#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "SDL2_gfxPrimitives.h"
#include "SDL2_gfxPrimitives_font.h"
#include "Utils.hpp"
#include "Engine.hpp"
#include "Planet.hpp"

using namespace std;

class Interface {
public:
  Interface( Engine* E );
  ~Interface();
  void draw();
  void draw_logo( int s = 300 );
  void draw_widget( int x, int y, int w, int h, int r = 5 );
  void draw_planet_info( Planet* p );
  void draw_planet_actions( Planet* p );
private:
  Engine* E;
};

#endif
