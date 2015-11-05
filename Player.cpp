#include "Player.hpp"

Player::Player( Engine* E, Interface* I, const string &name, Faction* faction )
:E(E), I(I), name(name), faction(faction), focused_planet(-1)
{
  if ( name == "zM" ) {
  	planets.push_back(new Planet(E, faction, Point(500, 150), 22.143));
  	planets.push_back(new Planet(E, faction, Point(1100, 400), 35.666));
  	planets.push_back(new Planet(E, faction, Point(720, 750), 42.314));
  	planets.push_back(new Planet(E, faction, Point(200, 350), 57.1337));
  	for ( int i = 0; i < 30; i++ ) {
  		planets.at(0)->ships.push_back(new Ship(E, faction, planets.at(0)));
  	}
    planets.at(0)->focus = 1;
  } else {
    planets.push_back(new Planet(E, faction, Point(620, 420), 74.1337));
  	for ( int i = 0; i < 10; i++ ) {
  		planets.at(0)->ships.push_back(new Ship(E, faction, planets.at(0)));
  	}
  }


}

Player::~Player()
{
  for ( unsigned i = 0; i < planets.size(); i++ ) {
    delete planets.at(i);
  }
}

void Player::update()
{

	// Gestion du pourcentage grâce aux touches numériques
	if ( E->keys[K_10P] ) {
			E->amount = 10;
	} else if ( E->keys[K_20P] ) {
			E->amount = 20;
	} else if ( E->keys[K_30P] ) {
			E->amount = 30;
	} else if ( E->keys[K_40P] ) {
			E->amount = 40;
	} else if ( E->keys[K_50P] ) {
			E->amount = 50;
	} else if ( E->keys[K_60P] ) {
			E->amount = 60;
	} else if ( E->keys[K_70P] ) {
			E->amount = 70;
	} else if ( E->keys[K_80P] ) {
			E->amount = 80;
	} else if ( E->keys[K_90P] ) {
			E->amount = 90;
	} else if ( E->keys[K_100P] ) {
			E->amount = 100;
	}

	// Gestion des touches haut et bas pour régler le pourcentage de vaisseaux
	if ( E->keys[K_CTRL] && E->keys[K_UP] == 1 ) {
		E->keys[K_UP] = 2;
		E->amount = min(100, E->amount+10);
	} else if ( E->keys[K_CTRL] && E->keys[K_DOWN] == 1 ) {
		E->keys[K_DOWN] = 2;
		E->amount = max(0, E->amount-10);
	}

  // Gestion des touches droite et gauche pour sélectionner une planète
  if ( E->keys[K_UP] == 1 || E->keys[K_RIGHT] == 1  || E->keys[K_DOWN] == 1  || E->keys[K_LEFT] == 1 ) {
    clearPlanetsFocus();
    if ( E->keys[K_UP] ) {
      E->keys[K_UP] = 2;
      focused_planet = findClosestPlanetIndex(planets.at(focused_planet), 0);
    }
    if ( E->keys[K_RIGHT] ) {
      E->keys[K_RIGHT] = 2;
      focused_planet = findClosestPlanetIndex(planets.at(focused_planet), 1);
    }
    if ( E->keys[K_DOWN] ) {
      E->keys[K_DOWN] = 2;
      focused_planet = findClosestPlanetIndex(planets.at(focused_planet), 2);
    }
    if ( E->keys[K_LEFT] ) {
      E->keys[K_LEFT] = 2;
      focused_planet = findClosestPlanetIndex(planets.at(focused_planet), 3);
    }
    planets.at(focused_planet)->focus = true;
  }

	for ( unsigned i = 0; i < planets.size(); i++ ) {
		planets.at(i)->update();
	}
}

//----
// Dessine tous les éléments controlés du joueur
void Player::draw()
{

	for ( unsigned i = 0; i < planets.size(); i++ ) {
		planets.at(i)->draw();
		if ( planets.at(i)->focus && name == "zM" ) {
			I->draw_planet_info(planets.at(i));
			I->draw_planet_actions(planets.at(i));
		}
	}

}

void Player::onMouseDown( SDL_Event* evt )
{

  unsigned i;

	for ( i = 0; i < planets.size(); i++ ) {
    if (
      E->circleCollide(&planets.at(i)->pos, &E->cursor, planets.at(i)->size)
    ) {
      planets.at(i)->select = 1;
      break;
      // if ( evt->button.button == SDL_BUTTON_LEFT ) {
      // } else {
      // }
    } else {
      planets.at(i)->select = 0;
      // if ( evt->button.button == SDL_BUTTON_LEFT ) {
      // } else {
      // }
    }
	}

}

void Player::onMouseUp( SDL_Event* evt )
{

  Planet* selected;
  bool ok = false;
  int n;
  unsigned i, j, k;

	for ( i = 0; i < planets.size(); i++ ) {
    n = 0;

    if (
      E->circleCollide(&planets.at(i)->pos, &E->cursor, planets.at(i)->size)
    ) {

      selected = selectedPlanet();

      // Si une planète est sélectionnée
      if ( selected != nullptr && selected == planets.at(i) ) {
        clearPlanetsFocus();
        planets.at(i)->focus = 1;
        planets.at(i)->select = 0;
      } else if ( selected != nullptr ) {

        if ( evt->button.button == SDL_BUTTON_LEFT ) {

          n = 0;
          for ( j = 0; j < selected->ships.size(); j++ ) {
            if ( !selected->ships.at(j)->is_traveling )
              n++;
          }

          selected->send(int(n*(float(E->amount)/100.0)), planets.at(i));
          ok = true;

        } else {

          selected->link_to( selected->sister == NULL ? planets.at(i) : NULL );
          ok = true;

        }

      }

    }
  }

  if ( !ok )
    clearPlanetsFocus();
  clearPlanetsSelect();

}

void Player::clearPlanetsFocus()
{
	for (unsigned j = 0; j < planets.size(); j++) {
		planets.at(j)->focus = 0;
	}
}

void Player::clearPlanetsSelect()
{
	for (unsigned j = 0; j < planets.size(); j++) {
		planets.at(j)->select = 0;
	}
}

Planet* Player::selectedPlanet()
{
  for ( unsigned i = 0; i < planets.size(); i++ ) {
    if ( planets.at(i)->select == 1 ) {
      return planets.at(i);
    }
  }

  return nullptr;
}

int Player::findClosestPlanetIndex( Planet* planet, int side )
{
	float dist, min;
	int index = 0;
	min = 0;
	for ( unsigned i = 0; i < planets.size(); i++ ) {
		if ( planet->pos.x != planets.at(i)->pos.x && planet->pos.y != planets.at(i)->pos.y ) {
			dist = sqrt(pow(planet->pos.y-planets.at(i)->pos.y, 2)+pow(planet->pos.x-planets.at(i)->pos.x, 2));
			if ( min == 0 ) {
				min = dist;
			} else {
				if ( min > dist ) {
					if (
								( side == 0 && planets.at(i)->pos.y < planet->pos.y )
						||	( side == 1 && planets.at(i)->pos.x > planet->pos.x )
						||	( side == 2 && planets.at(i)->pos.y > planet->pos.y )
						||	( side == 3 && planets.at(i)->pos.x < planet->pos.x )
					) {
						min = dist;
						index = i;
					}
				}
			}
		}
	}
	return index;
}
