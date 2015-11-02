#include "Entity.hpp"

Entity::Entity( Engine* E, Point pos, float size, const string &name, Entity* sister )
:E(E), pos(pos), size(size), speed(3), name(name), sister(sister)
{

}

Entity::~Entity()
{

}

int Entity::msg( int type )
{
  return 0;
}
