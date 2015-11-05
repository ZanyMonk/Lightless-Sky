#include <iostream>
#include <SDL2/SDL.h>
#include "Utils.hpp"
#include "Engine.hpp"
#include "Interface.hpp"
#include "Faction.hpp"
#include "Planet.hpp"
#include "Star.hpp"
#include "Ship.hpp"

class Player {
private:
  Engine* E;
  Interface* I;
public:
  Player( Engine* E, Interface* I, const string &name, Faction* faction );
  ~Player();
  void update();
  void draw();
  void onMouseDown( SDL_Event* evt );
  void onMouseUp( SDL_Event* evt );
  void clearPlanetsFocus();
  void clearPlanetsSelect();
  Planet* selectedPlanet();
  int findClosestPlanetIndex(Planet* planet, int side = -1);

  string name;
  Faction* faction;
  vector<Planet*> planets;
  int focused_planet;
};
