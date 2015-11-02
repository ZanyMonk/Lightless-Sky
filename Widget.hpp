#ifndef WIDGET_H
#define WIDGET_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "SDL2_gfx/SDL2_gfxPrimitives.h"
#include "Engine.hpp"
#include "Utils.hpp"
#include "Planet.hpp"

using namespace std;

class Widget {
private:
  Engine* E;
  Widget* parent;
public:
  Widget ( Engine* E, string name, Point pos, int h, int w, int r );
  Widget ( Engine* E, Widget* parent, string name, Point pos, int h, int w, int r );
  ~Widget ();
  void draw();

  int x, y, w, h, r;
  string name;
  Point pos;
};

#endif
