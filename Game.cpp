#include "Game.hpp"

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

/*
 * Game.cpp
 * Classe noyau du jeu Lightless Sky
 * Auteurs : L. Aubert et T. Borel-Grand
 * ---
 * 1) Inputs
 *	La gestion des inputs se fait grâce à un tableau d'entiers (keys) dont chaque élément
 *	correspond à une touche du clavier. Trois valeurs possibles :
 *			0		La touche n'est pas pressée
 *			1		La touche est pressée
 *			2		La touche est pressée et son effet a déjà été activé (throttle)
 *	Le throttle permet de ne pas activer l'effet d'un input à chaque frame pendant laquel-
 *	le la touche est pressée.
 */

const int BG_COLOR[] = {25,25,25};

// Touches de saisie du pourcentage
const SDL_Keycode K_10P = 38;
const SDL_Keycode K_20P = 233;
const SDL_Keycode K_30P = 34;
const SDL_Keycode K_40P = 39;
const SDL_Keycode K_50P = 40;
const SDL_Keycode K_60P = 45;
const SDL_Keycode K_70P = 232;
const SDL_Keycode K_80P = 95;
const SDL_Keycode K_90P = 231;
const SDL_Keycode K_100P = 224;
// Touches directionnelles
const SDL_Keycode K_RIGHT = 1073741903;
const SDL_Keycode K_LEFT = 1073741904;
const SDL_Keycode K_DOWN = 1073741905;
const SDL_Keycode K_UP = 1073741906;
const SDL_Keycode K_CTRL = 1073742048;

enum {
	UPDATE_INTERVAL = 1000/60
	, NB_SHIPS = 100
};

Game::Game( Engine* E )
:E(E), frameSkip(0), running(0), focused_planet(0), selected_planet(-1), throttle(false) {

	SDL_SetRenderDrawBlendMode(E->renderer,SDL_BLENDMODE_NONE);

	I = new Interface(E);
	screen = new Screen(E);

	planets.push_back(new Planet(E, Point(500, 200), 22.143));
	planets.push_back(new Planet(E, Point(1000, 400), 35.666));
	planets.push_back(new Planet(E, Point(700, 750), 42.314));
	planets.push_back(new Planet(E, Point(200, 350), 57.1337));

	for ( unsigned i = 0; i < planets.size(); i++ ) {
		planets.at(i)->planets = planets;
	}

	// REMOVE ME
	planets.at(0)->focus = true;
	planets.at(0)->sister = planets[1];
	planets.at(1)->sister = planets[3];
	planets.at(2)->sister = planets[1];

	for ( int i = 0; i < NB_SHIPS; i++ ) {
		planets.at(3)->ships.push_back(new Ship(E, planets.at(3)));
	}

}

Game::~Game() {
	this->stop();
		for ( unsigned i = 0; i < planets.size(); i++ ) {
			delete planets.at(i);
		}

	delete screen;
	delete I;
}

void Game::start() {
	this->running = 1;
	run();
}

void Game::stop() {

	if (NULL != E->renderer) {
		SDL_DestroyRenderer(E->renderer);
		E->renderer = NULL;
	}

	if (NULL != E->window) {
		SDL_DestroyWindow(E->window);
		E->window = NULL;
	}

	running = 0;
	SDL_Quit();

}

//---
//- Appelé quand l'événement Quit est activé
void Game::onQuit()
{

}

void Game::run() {
	int past = SDL_GetTicks();
	int now = past, pastFps = past;
	int fps = 0, framesSkipped = 0;
	SDL_Event event;

	boxRGBA(
		E->renderer,
		0, 0,
		E->display.w, E->display.h,
		BG_COLOR[0], BG_COLOR[1], BG_COLOR[2], 255
	);

	while ( running ) {
		int timeElapsed = 0;
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:    onQuit();            break;
				case SDL_KEYDOWN: onKeyDown( &event ); break;
				case SDL_KEYUP:   onKeyUp( &event );   break;
				case SDL_MOUSEBUTTONDOWN: onMouseDown( &event );		break;
				case SDL_MOUSEBUTTONUP:   onMouseUp( &event );			break;
				case SDL_MOUSEMOTION: 		onMouseMotion( &event );	break;
			}
		}
		// update/draw
		timeElapsed = (now=SDL_GetTicks()) - past;
		if ( timeElapsed >= UPDATE_INTERVAL ) {
			past = now;
			update();
			if ( framesSkipped++ >= frameSkip ) {
				draw();
				++fps;
				framesSkipped = 0;
			}
		}
		// fps
		if ( now - pastFps >= 1000 ) {
			pastFps = now;
			fps = 0;
		}
		// sleep?
		SDL_Delay( 10 );
	}
}

void Game::update() {

	// Arrêt du jeu
	if ( keys[SDLK_ESCAPE] || ( keys[SDLK_F4] && keys[SDLK_LALT] ) ) {
		stop();
	}

	// Gestion du pourcentage grâce aux touches numériques
	if ( keys[K_10P] ) {
			E->amount = 10;
	} else if ( keys[K_20P] ) {
			E->amount = 20;
	} else if ( keys[K_30P] ) {
			E->amount = 30;
	} else if ( keys[K_40P] ) {
			E->amount = 40;
	} else if ( keys[K_50P] ) {
			E->amount = 50;
	} else if ( keys[K_60P] ) {
			E->amount = 60;
	} else if ( keys[K_70P] ) {
			E->amount = 70;
	} else if ( keys[K_80P] ) {
			E->amount = 80;
	} else if ( keys[K_90P] ) {
			E->amount = 90;
	} else if ( keys[K_100P] ) {
			E->amount = 100;
	}

	// Gestion des touches droite et gauche pour sélectionner une planète
	if ( keys[K_UP] == 1 || keys[K_RIGHT] == 1  || keys[K_DOWN] == 1  || keys[K_LEFT] == 1 ) {
		clearPlanetsFocus();
		if ( keys[K_UP] ) {
			keys[K_UP] = 2;
			focused_planet = findClosestPlanetIndex(planets.at(focused_planet), 0);
		}
		if ( keys[K_RIGHT] ) {
			keys[K_RIGHT] = 2;
			focused_planet = findClosestPlanetIndex(planets.at(focused_planet), 1);
		}
		if ( keys[K_DOWN] ) {
			keys[K_DOWN] = 2;
			focused_planet = findClosestPlanetIndex(planets.at(focused_planet), 2);
		}
		if ( keys[K_LEFT] ) {
			keys[K_LEFT] = 2;
			focused_planet = findClosestPlanetIndex(planets.at(focused_planet), 3);
		}
		planets.at(focused_planet)->focus = true;
	}

	// Gestion des touches haut et bas pour régler le pourcentage de vaisseaux
	if ( keys[K_CTRL] && keys[K_UP] == 1 ) {
		keys[K_UP] = 2;
		E->amount = min(100, E->amount+10);
	} else if ( keys[K_CTRL] && keys[K_DOWN] == 1 ) {
		keys[K_DOWN] = 2;
		E->amount = max(0, E->amount-10);
	}


	for ( unsigned i = 0; i < planets.size(); i++ ) {
		planets.at(i)->update();
	}

}

void Game::draw() {
	// Clear screen
	boxRGBA(
		E->renderer,
		0, 0,
		E->display.w, E->display.h,
		BG_COLOR[0], BG_COLOR[1], BG_COLOR[2], 200
	);

	// Draw all planets
	for ( unsigned i = 0; i < planets.size(); i++ ) {
		planets.at(i)->draw();
		if ( planets.at(i)->focus ) {
			I->draw_planet_info(planets.at(i));
			I->draw_planet_actions(planets.at(i));
		}
	}

	// Draw interface
	I->draw();

	SDL_RenderPresent(E->renderer);
}

void Game::onMouseMotion( SDL_Event* evt ) {

	E->cursor._set(evt->button.x, evt->button.y);
	I->onMouseMotion( evt );

}

void Game::onMouseDown( SDL_Event* evt ) {
	E->click = true;
	I->onMouseDown( evt );

	for (unsigned j = 0; j < planets.size(); j++) {
		planets.at(j)->onMouseDown( evt );
	}

}

void Game::onMouseUp( SDL_Event* evt ) {
	E->click = false;
	selected_planet = -1;
	I->onMouseUp( evt );

	for (unsigned j = 0; j < planets.size(); j++) {
		planets.at(j)->onMouseUp( evt );
	}
}

void Game::onKeyDown( SDL_Event* evt ) {
	keys[ evt->key.keysym.sym ] = 1;

	// Print des infos sur la touche pressée
	printf("Physical %s key acting as %s key | Keycode: %d\n",
      SDL_GetScancodeName(evt->key.keysym.scancode),
      SDL_GetKeyName(evt->key.keysym.sym),
			evt->key.keysym.sym);
}

void Game::onKeyUp( SDL_Event* evt ) {
	keys[ evt->key.keysym.sym ] = 0;
}

void Game::clearPlanetsFocus()
{
	for (unsigned j = 0; j < planets.size(); j++) {
		planets.at(j)->focus = false;
	}
}

int Game::findClosestPlanetIndex( Planet* planet, int side )
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
