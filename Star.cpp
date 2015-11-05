#include "Star.hpp"

Star::Star( Engine* E, Faction* faction, Point pos, float size, const string &name )
:Planet(E, faction, pos, size, name, NULL)
{

}

Star::~Star()
{

}

void Star::draw()
{
  draw_planet();
}
