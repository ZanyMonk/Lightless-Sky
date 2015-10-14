#include "Planet.h"

Planet::Planet(Engine E)
:E(E), pos(Point(500,500)), size(20.0) {
}

Planet::Planet(Engine E, Point pos, float size)
:E(E), pos(pos), size(20.0) {
}

Planet::~Planet() {
}

void Planet::draw()
{

  filledCircleRGBA(
    E.renderer,
    pos.x, pos.y, size,
    101, 98, 92, 255
  );

}
