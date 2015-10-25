#include "Interface.hpp"

const int BUTTONS_SIZE = 30;
const int BUTTONS_RADIUS = 2;
const int BUTTONS_PADDING = 5;

Interface::Interface( Engine* E )
:E(E){
}

Interface::~Interface()
{
}

void Interface::draw()
{

}

//----
// Dessine l'insigne de l'Union
// Arguments :
//  int s   Taille de l'insigne en pixels
void Interface::draw_logo( int s )
{
  s = s/3;
  int x = E->display.w/2-(s*3)/2;
  int y = E->display.h/2-(s*3)/2;
  int black = 0xFF000100;
  int red = 0xFF0000FF;

  // Top trigon
  filledTrigonColor(
    E->renderer,
    x+s, y,
    x+s*2, y,
    x+s*2, y+s,
    black
  );

  // Right trigon
  filledTrigonColor(
    E->renderer,
    x+s*3, y+s,
    x+s*3, y+s*2,
    x+s*2, y+s*2,
    red
  );

  // Bottom trigon
  filledTrigonColor(
    E->renderer,
    x+s, y+s*2,
    x+s, y+s*3,
    x+s*2, y+s*3,
    black
  );

  // Left trigon
  filledTrigonColor(
    E->renderer,
    x, y+s,
    x, y+s*2,
    x+s, y+s,
    red
  );

}

//----
// Dessine une fenêtre stylisée.
// Arguments :
//  int x   origin point x
//  int y   origin point y
//  int r   radius
//  int h   height
//  int w   width
void Interface::draw_widget( int x, int y, int h, int w, int r )
{
  // On place les différents points de notre widget
  short int p_x[] = { x+r, x, x, x+w, x+w+r, x+w+r };
  short int p_y[] = { y, y+r, y+h, y+h, y+h-r, y };

  // On dessine le fond
  filledPolygonRGBA(
    E->renderer,
    p_x, p_y,
    6,
    255, 255, 255, 40
  );

  // Puis le contour
  E->draw_polygon(p_x, p_y, 6, 112, 189, 40, 255);

  aalineRGBA(
    E->renderer,
    x+r*2, y,
    x, y+r*2,
    112, 189, 40, 255
  );

  aalineRGBA(
    E->renderer,
    x+w-r, y+h,
    x+w+r, y+h-r*2,
    112, 189, 40, 255
  );

}

//----
// Dessine une petite fenêtre avec les informations concernant la planète sélectionnée
// Arguments :
//  Planet p  planète sélectionnée
void Interface::draw_planet_info( Planet* p )
{
  draw_widget(
    10, 10,
    100, 200
  );

  char buff[200];

	gfxPrimitivesSetFont(gfxPrimitivesFontdata, 8, 8);
  sprintf(buff, "Nom:    %s", p->name.c_str());
	stringRGBA(E->renderer, 20, 20, buff, 255, 255, 255, 255);
  sprintf(buff, "Taille: %d", int(p->size));
	stringRGBA(E->renderer, 20, 30, buff, 255, 255, 255, 255);
}


//----
// Dessine les actions disponibles pour la planète sélectionnée
void Interface::draw_planet_actions( Planet* p )
{
  int y = p->pos.y - ((BUTTONS_SIZE + BUTTONS_PADDING)*3) / 2;
  int x = p->pos.x + p->size + BUTTONS_PADDING*3;
  for ( int i = 0; i < 3; i++ ) {
    roundedRectangleRGBA(
      E->renderer,
      x, y + (BUTTONS_SIZE + BUTTONS_PADDING)*i,
      x + BUTTONS_SIZE, y + (BUTTONS_SIZE + BUTTONS_PADDING)*i + BUTTONS_SIZE,
      BUTTONS_RADIUS,
      255, 255, 255, 150
    );
  }
}
