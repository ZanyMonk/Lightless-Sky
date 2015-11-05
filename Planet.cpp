#include "Planet.hpp"

using namespace std;

/*----
 * Planet.cpp
 * Représente une planète.
 * Attributs :
 *  Engine E          Moteur de jeu
 *  Point pos         Position
 *  int size          Rayon
 *  int faction       Faction
 *    -1    Interdit
 *    0     Neutre
 *    1     Faction 1
 *    2     Faction 2 etc ...
 *  Planet* sister    Planète sœur, vers laquelle envoyer automatiquement les vaisseaux
 *  bool hover        Est sous le curseur
 *  bool focus        A la focalisation
 *  bool select       Est sélectionnée
 *  SDL_Texture* text_relief  Texture de la planète
 *  SDL_Texture* text_name    Texture du nom de la planète
 */

Planet::Planet( Engine* E, Faction* faction, Point pos, float size, const string &name, Planet* sister )
  :Entity(E, faction, pos, size, (name == "" ? generate_name(2, 4) : name)),
  sister(sister),
  hover(0),
  focus(0),
  select(0),
  text_name(nullptr)
{
  // text_relief = generate_text_relief();
}

Planet::~Planet()
{
	for ( unsigned i = 0; i < ships.size(); i++ ) {
		delete ships.at(i);
	}
}

void Planet::update()
{
  if ( text_name == nullptr ) {
    text_name = E->text_to_textureRGBA(name, 255, 255, 255, 255);
  }

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

  unsigned len, n;
  len = ships.size();

  if ( sister != NULL && len > 0 ) {
    for ( unsigned i = 0; i < len; i++ ) {
      if ( !ships.at(i)->is_traveling )
        n++;
    }
    if ( n > 0 ) {
      send(n, sister);
    }
  }
}

//----
// Dessine la planète et tous ses éléments annexes
void Planet::draw()
{

  draw_link();

  if ( select ) {
    if ( E->click == 1 ) {
      // On dessine un lien entre la planète sélectionnée et le curseur
      aalineRGBA(
        E->renderer,
        pos.x, pos.y,
        E->cursor.x, E->cursor.y,
        255, 255, 255, 255
      );
    } else {
      if ( sister == NULL ) {
        draw_link(&pos, &E->cursor);
      } else {
        draw_link(&pos, &E->cursor, 255, 0, 0);
      }
    }
  }

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

  // On dessine l'ombre de la planète
  draw_shadow();

  // On met à jour les positions et on dessine tous les vaisseaux apartenant à cette planète
  for ( unsigned i = 0; i < ships.size(); i++ ) {
    ships.at(i)->update();
    ships.at(i)->draw();
  }

  // E->draw_texture(text_relief, &pos);

}

SDL_Texture* Planet::generate_text_relief()
{

  int W, H, random;

  H = size*2;
  W = size*3.14;

  SDL_Texture* texture = SDL_CreateTexture(E->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, W, H);

  // TODO : Génération de la texture de la planète
  SDL_SetRenderTarget(E->renderer, texture);
  SDL_SetRenderDrawColor(E->renderer,0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(E->renderer);
  SDL_SetRenderDrawColor(E->renderer,0x00, 0x00, 0x00, 0xFF);

  for ( int i = 0; i < 100; i++ ) {
    srand(SDL_GetTicks());
    random = rand();
    SDL_Delay(1);
    SDL_RenderDrawPoint(E->renderer, random%W, random%H);
  }

  SDL_SetRenderTarget(E->renderer, NULL);

  return texture;

}

void Planet::draw_planet()
{

  aacircleRGBA(E->renderer, pos.x, pos.y, size, 101, 98, 92, 255);
  filledCircleRGBA(E->renderer, pos.x, pos.y, size, 101, 98, 92, 255);

}

//----
// Dessine le lien entre cette planète et sa planète réceptrice
void Planet::draw_link( Point* pos1, Point* pos2, Uint8 r, Uint8 g, Uint8 b )
{
  short int distance, x1, y1, x2, y2, radius;
  float speed, mod, amplitude, x, y, step, coefficient, sincos;
  bool args = (pos1 != nullptr && pos2 != nullptr);
  if ( args ) {
    x1 = x = pos1->x;
    y1 = y = pos1->y;
    x2 = pos2->x;
    y2 = pos2->y;
  } else if ( sister != NULL ) {
    x1 = x = pos.x;
    y1 = y = pos.y;
    x2 = sister->pos.x;
    y2 = sister->pos.y;
  }

  if ( args || sister != NULL ) {

    speed = 1;
    mod = 0.01;
    amplitude = 0.15;

    // Distance entre les deux planètes
    distance = abs(x2-x1);
    // Pas utilisé, équivalent à la variable temps
    step = SDL_GetTicks()/((E->display.w-distance)*(1+mod));
    // Coefficient directeur
    coefficient = float(y1-y2)/float(x1-x2);

    radius = (x1 > x2 ? -1 : 1);

    SDL_SetRenderDrawBlendMode(E->renderer, SDL_BLENDMODE_BLEND);

    for ( float i = 0; i < distance*mod; i+=mod ) {
      sincos = sin(i+step*coefficient)*cos(i+step*coefficient);
      x += sincos*(amplitude+i/5)*-coefficient+speed*radius;
      y += sincos*(amplitude+i/5)+speed*coefficient*radius;

      for ( int j = 0; j < LINK_GLOW_WIDTH; j++ ) {
      	SDL_SetRenderDrawColor(
          E->renderer,
          r, g, b,
          (j>LINK_GLOW_WIDTH/2 ? LINK_GLOW_WIDTH-j : j)+10
        );
        SDL_RenderDrawPoint(
          E->renderer,
          x-LINK_GLOW_WIDTH/2+j*-coefficient+speed*radius,
          y-LINK_GLOW_WIDTH/2+j+speed*coefficient*radius
        );
      }
    }

  }

}

//----
// Dessine une lueur derrière la planète
void Planet::draw_glow()
{

  int x, y, width, opacity, r, g, b;
  float alpha;
  width = size*4;

  r = faction->color.r;
  g = faction->color.g;
  b = faction->color.b;

  SDL_SetRenderDrawBlendMode(E->renderer, SDL_BLENDMODE_BLEND);
  opacity = ( focus && hover == 0 ? HOVER_GLOW_ALPHA : hover );

  for ( y = 0; y < width; y++ ) {
    for ( x = 0; x < width; x++ ) {
      alpha = (width-sqrt(pow(width/2-x, 2)+pow(width/2-y, 2))*2)/size;

      if ( alpha*opacity > 0 ) {
        // if ( x == y && opacity != 15 )
        //   cout << alpha << "\t" << int(alpha*opacity) << endl;
        SDL_SetRenderDrawColor(E->renderer, r, g, b, int(alpha*opacity));
        SDL_RenderDrawPoint(E->renderer, pos.x-width/2+x, pos.y-width/2+y);
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

  SDL_SetRenderDrawBlendMode(E->renderer, SDL_BLENDMODE_BLEND);

  for ( y = 0; y < width+1; y++ ) {
    for ( x = 0; x < width+1; x++ ) {
      alpha = min(max(0.0,
        sqrt(pow(size-y, 2)+pow(size-x, 2))*((100-size)/15)-(size*5-(x+y)*1.4)
      ), 255.0);

      if (
        pow(size+0.2-y, 2)+pow(size+0.2-x, 2) < pow(size, 2)
      ) {
        SDL_SetRenderDrawColor(E->renderer, 0, 0, 0, alpha);
        SDL_RenderDrawPoint(E->renderer, pos.x-size+x+1, pos.y-size+y+1);
      }
    }
  }

}

//----
// Lie cette planète avec une sœur
// Arguments :
//  Planet* sister    Planète sœur à qui se lier
void Planet::link_to( Planet* new_sister )
{
  if (
    new_sister == NULL
    || new_sister->sister == NULL
    || new_sister->sister != this
  ) {
    sister = new_sister;
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
