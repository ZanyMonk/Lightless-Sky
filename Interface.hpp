#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "SDL2_gfx/SDL2_gfxPrimitives.h"
#include "SDL2_gfx/SDL2_gfxPrimitives_font.h"
#include "Utils.hpp"
#include "Engine.hpp"
#include "Widget.hpp"
#include "Planet.hpp"

using namespace std;

class Interface {
public:
  Interface( Engine* E );
  ~Interface();
  void onMouseMotion( SDL_Event* evt );
  void onMouseDown( SDL_Event* evt );
  void onMouseUp( SDL_Event* evt );
  void draw();
  void draw_logo( Point pos, int s = 300 );
  // void draw_widget( int x, int y, int w, int h, int r = 5 );
  // void draw_widget( int x, int y, int w, int h, Planet* planet, int r = 5 );
  void draw_slider();
  void draw_planet_info( Planet* p );
  void draw_planet_actions( Planet* p );
private:
  Engine* E;
  bool sliding;
  int sb_s, sb_x, sb_y;
  vector<Widget*> widgets;
  string name;
};

#endif
