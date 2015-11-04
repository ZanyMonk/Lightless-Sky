#include "Interface.hpp"

const int BUTTONS_SIZE = 30;
const int BUTTONS_RADIUS = 2;
const int BUTTONS_PADDING = 5;
const int SLIDER_PADDING = 7;
const int SLIDER_HEIGHT = 8+SLIDER_PADDING*2;
const int SLIDER_BAR_WIDTH = 2;

Interface::Interface( Engine* E )
:E(E), sliding(false) {

  // Variables pour la slide bar
  sb_s = E->display.w/2;
  sb_x = E->display.w/2-sb_s/2;
  sb_y = E->display.h-(SLIDER_HEIGHT+5);

  widgets.push_back(new Widget(
    E,
    "planet_info",
    Point(10, 10),
    205, 100, 5
  ));

  widgets.push_back(new Widget(
    E,
    widgets.at(0),
    "planet_info_sister",
    Point(10, 120),
    80, 50, 5
  ));

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
    || (
         E->click
      && evt->button.x > sb_x && evt->button.x < sb_x+sb_s
      && evt->button.y > sb_y
    )
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
void Interface::draw_logo( Point pos, int s )
{
  s = s/3;
  int x = pos.x-(s*3)/2;
  int y = pos.y-(s*3)/2;

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

  widgets.at(0)->draw();

  char buff[200];

  sprintf(buff, "Nom:%s%s", E->multString(" ", 20-p->name.length()).c_str(), p->name.c_str());
	stringColor(E->renderer, 20, 20, buff, WHITE);
  sprintf(buff, "Rayon:%s%d km", E->multString(" ", 15-to_string(int(p->size*500)).length()).c_str(), int(p->size*500));
	stringColor(E->renderer, 20, 32, buff, WHITE);

  if ( p->sister != NULL ) {
    widgets.at(1)->draw();
  }
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
