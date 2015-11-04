#include "Entity.hpp"

Entity::Entity( Engine* E, Point pos, float size, const string &name )
:E(E), pos(pos), size(size), speed(3), name(name)
{
  seed = SDL_GetTicks();
  srand(seed);
  seed = rand();
  SDL_Delay(1);
}

Entity::~Entity()
{

}

void Entity::update() { }
void Entity::draw() { }
