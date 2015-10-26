#include <SDL2/SDL.h>
#include "SDL2_gfx/SDL2_gfxPrimitives.h"
#include "Utils.hpp"
#include "Engine.hpp"

class Screen {
public:
  Screen( Engine* E );
  ~Screen();
private:
  Engine* E;
};
