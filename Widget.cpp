#include "Widget.hpp"

Widget::Widget( Engine* E, string name, Point pos, int w, int h, int r )
:E(E), parent(NULL), w(w), h(h), r(r), name(name), pos(pos)
{

}

Widget::Widget( Engine* E, Widget* parent, string name, Point pos, int w, int h, int r )
:E(E), parent(parent), w(w), h(h), r(r), name(name), pos(pos)
{

}

Widget::~Widget()
{

}

//----
// Dessine une fenêtre stylisée.
// Arguments :
//  int x   origin point x
//  int y   origin point y
//  int h   height
//  int w   width
//  int r   radius
void Widget::draw()
{
  // On dessine le lien si on est lié
  if ( parent != NULL ) {

    lineColor(
      E->renderer,
      pos.x+r*2+1, pos.y,
      parent->pos.x+r*2+1, parent->pos.y+parent->h,
      GREEN
    );
    lineColor(
      E->renderer,
      pos.x+r*2+5, pos.y,
      parent->pos.x+r*2+5, parent->pos.y+parent->h,
      GREEN
    );
    lineColor(
      E->renderer,
      pos.x-r+w-1, pos.y,
      parent->pos.x-r+w-1, parent->pos.y+parent->h,
      GREEN
    );
    lineColor(
      E->renderer,
      pos.x-r+w-5, pos.y,
      parent->pos.x-r+w-5, parent->pos.y+parent->h,
      GREEN
    );
  }

  // On place les différents points de notre widget
  short int p_x[] = { short(pos.x+r), short(pos.x), short(pos.x), short(pos.x+w), short(pos.x+w+r), short(pos.x+w+r) };
  short int p_y[] = { short(pos.y), short(pos.y+r), short(pos.y+h), short(pos.y+h), short(pos.y+h-r), short(pos.y) };

  // On dessine le fond
  filledPolygonColor(
    E->renderer,
    p_x, p_y,
    6,
    GRAY
  );

  // Puis le contour
  E->draw_polygon(p_x, p_y, 6, GREEN);

  aalineColor(
    E->renderer,
    pos.x+r*2, pos.y,
    pos.x, pos.y+r*2,
    GREEN
  );

  aalineColor(
    E->renderer,
    pos.x+w-r, pos.y+h,
    pos.x+w+r, pos.y+h-r*2,
    GREEN
  );

}
