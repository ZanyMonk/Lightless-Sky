#include "Star.hpp"

Star::Star( Engine* E, Point pos, float size, int faction, const string &name )
:Planet(E, pos, size, faction, name, NULL)
{

}

Star::~Star()
{

}

void Star::draw()
{
  draw_planet();
}
