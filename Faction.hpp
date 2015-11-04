#ifndef FACTION_H
#define FACTION_H

#include <iostream>
#include <SDL2/SDL.h>
#include "Utils.hpp"

using namespace std;

class Faction {
private:
public:
  Faction( const string &name, SDL_Color color );
  Faction( const string &name, Uint8 r, Uint8 g, Uint8 b, Uint8 a );
  ~Faction();

  SDL_Color* color;
  string name;
};

#endif
