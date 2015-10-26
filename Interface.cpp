#include "Interface.hpp"

const int BUTTONS_SIZE = 30;
const int BUTTONS_RADIUS = 2;
const int BUTTONS_PADDING = 5;
const int SLIDER_PADDING = 7;
const int SLIDER_HEIGHT = 8+SLIDER_PADDING*2;
const int SLIDER_BAR_WIDTH = 2;

// Couleurs
//      vert   bleu
//          \  /
//    0xAABBCCDD
//      /  \
// opacité rouge
const int GREEN = 0xFF3ECC1B;
const int BLACK = 0xFF000000;
const int RED = 0xFF0000FF;
const int GRAY = 0x2254778C;
const int WHITE = 0xFFFFFFFF;

Interface::Interface( Engine* E )
:E(E), sliding(false) {

  gfxPrimitivesSetFont(gfxPrimitivesFontdata, 8, 8);

  // Variables pour la slide bar
    sb_s = E->display.w/2;
    sb_x = E->display.w/2-sb_s/2;
    sb_y = E->display.h-(SLIDER_HEIGHT+5);

}

Interface::~Interface()
{
}

void Interface::onMouseMotion( SDL_Event* evt )
{
  int a = E->amount;
  int w = (8*(to_string(a).length()+2))+SLIDER_PADDING*4;

  // Si on clique sur la slide bar
  if (
       sliding
    || E->click
    && evt->button.x > sb_x && evt->button.x < sb_x+sb_s
    && evt->button.y > sb_y
  ) {
    sliding = true;
    E->amount = max(0, min((evt->button.x-sb_x-w/2)/(sb_s/100)+2, 100));
  }
}

void Interface::onMouseDown( SDL_Event* evt )
{
  int a = E->amount;
  int w = (8*(to_string(a).length()+2))+SLIDER_PADDING*4;

  // Si on clique sur la slide bar
  if (
       evt->button.x > sb_x && evt->button.x < sb_x+sb_s
    && evt->button.y > sb_y
  ) {
    E->amount = max(0, min((evt->button.x-sb_x-w/2)/(sb_s/100)+2, 100));
  }
}

void Interface::onMouseUp( SDL_Event* evt )
{
  sliding = false;
}

void Interface::draw()
{
  draw_slider();
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

  // Top trigon
  filledTrigonColor(
    E->renderer,
    x+s, y,
    x+s*2, y,
    x+s*2, y+s,
    BLACK
  );

  // Right trigon
  filledTrigonColor(
    E->renderer,
    x+s*3, y+s,
    x+s*3, y+s*2,
    x+s*2, y+s*2,
    RED
  );

  // Bottom trigon
  filledTrigonColor(
    E->renderer,
    x+s, y+s*2,
    x+s, y+s*3,
    x+s*2, y+s*3,
    BLACK
  );

  // Left trigon
  filledTrigonColor(
    E->renderer,
    x, y+s,
    x, y+s*2,
    x+s, y+s,
    RED
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
  filledPolygonColor(
    E->renderer,
    p_x, p_y,
    6,
    GRAY
  );

  // Puis le contour
  E->draw_polygon(p_x, p_y, 6, 112, 189, 40, 255);

  aalineColor(
    E->renderer,
    x+r*2, y,
    x, y+r*2,
    GREEN
  );

  aalineColor(
    E->renderer,
    x+w-r, y+h,
    x+w+r, y+h-r*2,
    GREEN
  );

}

//----
// Dessine le widget permettant la sélection du pourcentage de troupes à déplacer
void Interface::draw_slider()
{
  int a = E->amount;
  int w = (8*(to_string(a).length()+2))+SLIDER_PADDING*4;
  char buff[10];
  sprintf(buff, "%d %%", a);

  rectangleColor(
    E->renderer,
    sb_x, sb_y+(SLIDER_HEIGHT/2-SLIDER_BAR_WIDTH/2),
    sb_x+sb_s, sb_y+(SLIDER_HEIGHT/2+SLIDER_BAR_WIDTH/2),
    GREEN
  );

  boxColor(
    E->renderer,
    (sb_s/100)*a+sb_x-w/2, sb_y,
    (sb_s/100)*a+sb_x+w/2, sb_y+SLIDER_HEIGHT,
    BLACK
  );

  rectangleColor(
    E->renderer,
    (sb_s/100)*a+sb_x-w/2, sb_y,
    (sb_s/100)*a+sb_x+w/2, sb_y+SLIDER_HEIGHT,
    GREEN
  );

  stringColor(E->renderer, (sb_s/100)*a-w/2+sb_x+SLIDER_PADDING*2, sb_y+SLIDER_PADDING, buff, GREEN);
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

  sprintf(buff, "Nom:    %s", p->name.c_str());
	stringColor(E->renderer, 20, 20, buff, WHITE);
  sprintf(buff, "Taille: %d", int(p->size));
	stringColor(E->renderer, 20, 30, buff, WHITE);
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
