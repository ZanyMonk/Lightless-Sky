#include "Planet.hpp"

/*----
 * Planet.cpp
 * Représente une planète.
 * Attributs :
 *  Engine E    Moteur de jeu
 *  Point pos   Position
 *  int size    Rayon
 *  bool hover  Est sous le curseur
 *  bool focus  Est sélectionnée
 */

Planet::Planet( Engine* E, Point position, float size, string name )
:E(E), pos(position), size(size), hover(0), focus(0), name(name) {
}

Planet::Planet( Engine* E, int x, int y, float size, string name )
:E(E), pos(Point(x, y)), size(size), hover(0), focus(0), name(name) {
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

  if ( hover || focus ) {
    draw_glow();
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
      255, 255, 255, ( focus ? 7 : hover/4 )
    );
	}
}
