#ifndef STAR_H
#define STAR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "Utils.hpp"
#include "Engine.hpp"
#include "Planet.hpp"

class Star : public Planet {
private:
public:
  Star( Engine* E, Faction* faction, Point pos, float size, const string &name = "" );
  ~Star();
  void draw();
};

#endif
