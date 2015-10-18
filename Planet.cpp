#include "Planet.h"

const int HOVER_GLOW_ALPHA = 15;

Planet::Planet(Engine* E)
:E(E), pos(Point(500,500)), size(20.0), hover(0) {
}

Planet::Planet(Engine* E, Point position, float size)
:E(E), pos(position), size(size), hover(0) {
}

Planet::Planet(Engine* E, int x, int y, float size)
:E(E), pos(Point(x, y)), size(size), hover(0) {
}

Planet::~Planet() {
}

void Planet::draw()
{

  if (
    pow( pos.x - E->cursor.x, 2 ) + pow( pos.y - E->cursor.y, 2 )
      < pow( size, 2 )
  ) {
    if ( !hover ) {
      hover = 1;
    } else if ( hover < HOVER_GLOW_ALPHA ) {
      hover++;
    }
  } else if (hover) {
    hover -= 1;
  } else {
    hover = 0;
  }

  draw_glow();

  filledCircleRGBA(
    E->renderer,
    pos.x, pos.y, size,
    101, 98, 92, 255
  );

  filledCircleRGBA(
    E->renderer,
    pos.x, pos.y, size+1,
    101, 98, 92, 155
  );

}

void Planet::draw_glow()
{
  // int elapsed = SDL_GetTicks() - hover;
  // int alpha = elapsed < 150 ? elapsed/10 : 15;
  if ( hover ) {
  	for ( int i = 1; i < 5; i++ ) {
      filledCircleRGBA(
        E->renderer,
        pos.x, pos.y, size+(4*i),
        255, 255, 255, hover
      );
  	}
  }
}
