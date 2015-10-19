#include "Planet.h"

const int HOVER_GLOW_ALPHA = 15;
const int BUTTONS_SIZE = 30;
const int BUTTONS_RADIUS = 2;
const int BUTTONS_PADDING = 5;

Planet::Planet(Engine* E, Point position, float size)
:E(E), pos(position), size(size), hover(0), focus(0) {
}

Planet::Planet(Engine* E, int x, int y, float size)
:E(E), pos(Point(x, y)), size(size), hover(0), focus(0) {
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

  if ( hover ) {
    draw_glow();
  }

  if ( focus ) {
    draw_options();
  }

  filledCircleRGBA(
    E->renderer,
    pos.x, pos.y, size,
    101, 98, 92, 255
  );

  filledCircleRGBA(
    E->renderer,
    pos.x, pos.y, size+1,
    101, 98, 92, 120
  );

}

//----
// Draws a glow effect. Used as hovering effect.
void Planet::draw_glow()
{
	for ( int i = 1; i < 5; i++ ) {

    filledCircleRGBA(
      E->renderer,
      pos.x, pos.y, size+(4*i),
      255, 255, 255, hover
    );
	}
}

//----
// Draws option buttons on the side of the planet.
void Planet::draw_options()
{
  int y = pos.y - ((BUTTONS_SIZE + BUTTONS_PADDING)*3) / 2;
  int x = pos.x + size + BUTTONS_PADDING*3;
  for ( int i = 0; i < 3; i++ ) {
    roundedRectangleRGBA(
      E->renderer,
      x, y + (BUTTONS_SIZE + BUTTONS_PADDING)*i,
      x + BUTTONS_SIZE, y + (BUTTONS_SIZE + BUTTONS_PADDING)*i + BUTTONS_SIZE,
      BUTTONS_RADIUS,
      255, 255, 255, ( focus ? HOVER_GLOW_ALPHA*10 : 0 )
    );
  }
}
