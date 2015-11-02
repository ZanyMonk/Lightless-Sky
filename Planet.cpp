#include "Planet.hpp"

using namespace std;

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

Planet::Planet( Engine* E, Point pos, float size, const string &name )
  :Entity(E, pos, size, (name == "" ? generate_name(2, 4) : name), NULL),
  hover(0),
  focus(0),
  select(0),
  text_name(nullptr)
{

  seed = SDL_GetTicks();
  srand(seed);
  seed = rand();
  SDL_Delay(1);
}

Planet::~Planet()
{
	for ( unsigned i = 0; i < ships.size(); i++ ) {
		delete ships.at(i);
	}
}

void Planet::update()
{
  // TODO : Génération de texture aléatoire

  // On fait une transition entre les valeurs 0 et HOVER_GLOW_ALPHA d'opacité du nom de la planète
  // et de son effet de survol.
  if ( !focus ) {
    if (
      pow( pos.x - E->cursor.x, 2 ) + pow( pos.y - E->cursor.y, 2 ) < pow( size, 2 )
    ) {
      if ( !hover ) {
        hover = 1;
      } else if ( hover < HOVER_GLOW_ALPHA ) {
        hover += 2;
      }
    } else if (hover) {
      hover--;
    } else {
      hover = 0;
    }
  }

  // Si on n'a pas encore généré la texture du nom de la planète, on le fait
  if ( text_name == nullptr ) {
    text_name = E->text_to_textureRGBA(name, FONT_PATH, 255, 255, 255, 255, 12);
  }
}

//----
// Dessine la planète et tous ses éléments annexes
void Planet::draw()
{

  // draw_link();

  if ( hover || focus ) {
    draw_glow();
  }

  draw_planet();

  if ( hover || focus || select ) {
    // On dessine la texture du nom de la planète avec l'opacité qui va bien
    E->draw_texture(
      text_name,
      new Point(pos.x, pos.y+size+20),
      (focus ? HOVER_GLOW_ALPHA*10 : hover*10)
    );
  }

  if ( select ) {
    // On dessine un lien entre la planète sélectionnée et le curseur
    lineRGBA(
      E->renderer,
      pos.x, pos.y,
      E->cursor.x, E->cursor.y,
      255, 255, 255, 255
    );
  }

  // On met à jour les positions et on dessine tous les vaisseaux apartenant à cette planète
  for ( unsigned i = 0; i < ships.size(); i++ ) {
    ships.at(i)->update();
    ships.at(i)->draw();
  }

  // On dessine l'ombre de la planète
  // draw_shadow();

}

//----
// Appelé au clique
void Planet::onMouseDown( SDL_Event* evt )
{
  if (
    // Si collision curseur/planète
    pow( pos.x - E->cursor.x, 2 ) + pow( pos.y - E->cursor.y, 2 )
      < pow( size, 2 )
  ) {
    if ( evt->button.button == SDL_BUTTON_LEFT ) {
      select = 1;
    } else {
      focus = 1;
    }
  } else {
    select = 0;
    focus = 0;
    // if ( evt->button.button == SDL_BUTTON_LEFT ) {
    // } else {
    // }
  }

}

//----
// Appelé au lâché de clique
void Planet::onMouseUp( SDL_Event* evt )
{

  if (
    // Si collision curseur/planète
    pow( pos.x - E->cursor.x, 2 ) + pow( pos.y - E->cursor.y, 2 )
      < pow( size, 2 )
  ) {
    // if ( evt->button.button == SDL_BUTTON_LEFT ) {
    // } else {
    // }
  } else {
    if ( evt->button.button == SDL_BUTTON_LEFT ) {
      if ( select == 1 ) {
        for ( unsigned i = 0; i < planets.size(); i++ ) {
          if (
            // Si collision curseur/planète
            pow( planets.at(i)->pos.x - E->cursor.x, 2 ) + pow( planets.at(i)->pos.y - E->cursor.y, 2 )
              < pow( planets.at(i)->size, 2 )
          ) {
            send(int(ships.size()*(float(E->amount)/100.0)), planets.at(i));
            break;
          }
        }
      }
    }
    focus = 0;
    select = 0;
  }

}

void Planet::draw_planet()
{

    int x, y, width;
    float pos_x, pos_y;
    width = int(size*2);
    pos_x = pos.x-width/2;
    pos_y = pos.y-width/2;

    SDL_SetRenderDrawColor(E->renderer, 101, 98, 92, 0xFF);

    for ( y = 0; y < width+1; y++ ) {
      for ( x = 0; x < width+1; x++ ) {
        if ( pow(pos.x - pos_x-x, 2)+pow(pos.y - pos_y-y, 2) < pow(size, 2) ) {
          SDL_RenderDrawPoint(E->renderer, pos_x+x, pos_y+y);
        }
      }
    }

}

//----
// Dessine le lien entre cette planète et sa planète réceptrice
void Planet::draw_link()
{
  if ( sister != NULL ) {

    short int distance, x1, y1, x2, y2, r;
    float speed, mod, amplitude, x, y, step, coefficient, sincos;
    Point handle = Point(700, 300);

    speed = 1;
    mod = 0.01;
    amplitude = 0.15;

    x1 = x = pos.x;
    y1 = y = pos.y;
    x2 = sister->pos.x;
    y2 = sister->pos.y;

    // Distance entre les deux planètes
    distance = abs(x2-x1);
    // Pas utilisé, équivalent à la variable temps
    step = SDL_GetTicks()/((E->display.w-distance)*(1+mod));
    // Coefficient directeur
    coefficient = float(y1-y2)/float(x1-x2);

    r = (x1 > x2 ? -1 : 1);

    for ( float i = 0; i < distance*mod; i+=mod ) {
      sincos = sin(i+step*coefficient)*cos(i+step*coefficient);
      x += sincos*(amplitude+i/5)*-coefficient+speed*r;
      y += sincos*(amplitude+i/5)+speed*coefficient*r;

      for ( int j = 0; j < LINK_GLOW_WIDTH; j++ ) {
      	SDL_SetRenderDrawColor(
          E->renderer,
          0xFF, 0xFF, 0xFF,
          (j>LINK_GLOW_WIDTH/2 ? LINK_GLOW_WIDTH-j : j)
        );
        SDL_RenderDrawPoint(
          E->renderer,
          x-LINK_GLOW_WIDTH/2+j*-coefficient+speed*r,
          y-LINK_GLOW_WIDTH/2+j+speed*coefficient*r
        );
      }
    }

  }

}

//----
// Dessine une lueur derrière la planète
void Planet::draw_glow()
{

  int x, y, width, opacity;
  float pos_x, pos_y, alpha;
  width = size*4;
  pos_x = pos.x-width/2;
  pos_y = pos.y-width/2;

  opacity = ( focus && hover == 0 ? HOVER_GLOW_ALPHA : hover );

  for ( y = 0; y < width; y++ ) {
    for ( x = 0; x < width; x++ ) {
      alpha = (width-sqrt(pow(pos.x - pos_x-x, 2)+pow(pos.y - pos_y-y, 2))*2)/size;

      if ( alpha*opacity > 0 ) {
        if ( x == y && opacity != 15 )
          cout << alpha << "\t" << int(alpha*opacity) << endl;
        SDL_SetRenderDrawColor(E->renderer, 0xFF, 0xFF, 0xFF, int(alpha*opacity));
        SDL_RenderDrawPoint(E->renderer, pos_x+x, pos_y+y);
      }
    }
  }

}

//----
// Dessine l'ombre de la planète
void Planet::draw_shadow()
{

  int x, y, width;
  float alpha;
  width = size*2;


  for ( y = 0; y < width; y++ ) {
    for ( x = 0; x < width+2; x++ ) {
      alpha = x;

      if ( y == 0 )
        cout << x << endl;

      if ( alpha > 0 ) {
        SDL_SetRenderDrawColor(E->renderer, 0, 0, 0, int(alpha));
        SDL_RenderDrawPoint(E->renderer, pos.x-size+x, pos.y-size+y+1);
      }
    }
  }

}

//----
// Envoie n vaisseaux sur la planète target
// Arguments :
// int n          Nombre de vaisseaux
// Planet* target Pointeur vers la planète ciblée
int Planet::send( int n, Planet* target )
{
  int len = ships.size();
  cout << "len = " << len << endl;
  n = (n > len ? len : n);
  if ( n > 0 ) {
    for ( unsigned i = len-1; i >= 0; i-- ) {
      n--;
      if ( n < 0 ) {
        break;
      } else {
        ships.at(i)->head_to(target);
        target->ships.push_back(ships.at(i));
        ships.pop_back();
      }
    }
  }

  return 0;
}

//----
// Utilisé pour transmettre des messages entre les entités
// Arguments :
// int  Type de message (0 = pass_ship_to_sister)
int Planet::msg( int type )
{
  return 0;
  // switch (type) {
  //   case 0:
  //     Planet* target = sister;
  //     send(1, target);
  //     return 0;
  //   default:
  //     cout << type << endl;
  //     return -1;
  // }
}

//----
// Génère un nom aléatoire à partir d'un dictionnaire de phonemes
// Arguments :
// Uint8 min  Longueur minimum
// Uint8 max  Longueur maximum
string Planet::generate_name( Uint8 min, Uint8 max)
{
  vector<string> phonemes = {
    "-", "'", "ka", "ri", "ko", "ro", "ru", "cor", "syr", "sur", "tus", "tan", "too", "li",
    "la", "do", "di", "va", "vi", "fer", "fus", "fez", "zul", "xin", "xy", "par"
  };
  string str;
  int len = rand()%(max-min)+min;
  int m;
  for ( int i = 0; i < len; i++ ) {
    m = (i == 0 || i == len-1 ? 2 : 0);
    str = str+phonemes[rand()%(phonemes.size()-m)+m];
  }
  str[0] = toupper(str[0]);
  return str;
}
