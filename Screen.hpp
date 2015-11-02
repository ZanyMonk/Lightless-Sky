#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "SDL2_gfx/SDL2_gfxPrimitives.h"
#include "Utils.hpp"
#include "Engine.hpp"

using namespace std;

class Screen {
public:
  Screen( Engine* E );
  ~Screen();
private:
  Engine* E;
};
