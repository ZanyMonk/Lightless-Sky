#include "Entity.hpp"

Entity::Entity( Engine* E, Faction* faction, Point pos, float size, const string &name )
:E(E), faction(faction), pos(pos), size(size), speed(3), name(name)
{
  seed = SDL_GetTicks();
  srand(seed);
  seed = rand();
  SDL_Delay(2);
}

Entity::~Entity()
{

}

void Entity::update() { }
void Entity::draw() { }
