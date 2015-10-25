#include "Game.hpp"

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

const int BG_COLOR[] = {25,25,25};

using namespace std;

enum {
	UPDATE_INTERVAL = 1000/60
	, NB_SHIPS = 10
};

Game::Game( Engine* E )
:E(E), frameSkip(0), running(0), click(false) {
	I = new Interface(E);
	planets.push_back(new Planet(E, Point(500, 200), 20.0));
	planets.push_back(new Planet(E, Point(1000, 400), 30.0));
	planets.push_back(new Planet(E, Point(700, 750), 25.0));
	planets.push_back(new Planet(E, Point(200, 400), 50.0));

	planets.at(0)->focus = true;

	for ( int i = 0; i < NB_SHIPS; i++ ) {
		ships.push_back(new Ship(E, *planets[0]));
	}
}

Game::~Game() {
	this->stop();

		for ( int i = 0; i < NB_SHIPS; i++ ) {
			delete ships[i];
		}

		for ( unsigned i = 0; i < planets.size(); i++ ) {
			delete planets.at(i);
		}

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

	if ( keys[SDLK_ESCAPE] || ( keys[SDLK_F4] && keys[SDLK_LALT] ) ) {
		stop();
	}

	for ( unsigned i = 0; i < ships.size(); i++ ) {
		ships.at(i)->update();
	}

}

void Game::draw() {
	// Clear screen
	SDL_SetRenderDrawColor(E->renderer, BG_COLOR[0], BG_COLOR[1], BG_COLOR[2], 50);
	boxRGBA(
		E->renderer,
		0, 0,
		E->display.w, E->display.h,
		BG_COLOR[0], BG_COLOR[1], BG_COLOR[2], 120
	);

	// Draw all planets
	for ( unsigned i = 0; i < planets.size(); i++ ) {
		planets.at(i)->draw();
		if ( planets.at(i)->focus ) {
			I->draw_planet_info(planets.at(i));
			I->draw_planet_actions(planets.at(i));
		}
	}

	// Draw all ships
	for ( unsigned i = 0; i < ships.size(); i++ ) {
		ships.at(i)->draw();
	}

	// Draw interface
	I->draw();

	SDL_RenderPresent(E->renderer);
}

void Game::onMouseMotion( SDL_Event* evt ) {

	E->cursor._set(evt->button.x, evt->button.y);

}

void Game::onMouseDown( SDL_Event* evt ) {
	click = true;

	clearPlanetsFocus( evt );

	if ( evt->button.button == SDL_BUTTON_RIGHT ) {
		for (unsigned j = 0; j < planets.size(); j++) {
			if (
				// If collision cursor/planet
				pow( planets.at(j)->pos.x - evt->button.x, 2 ) + pow( planets.at(j)->pos.y - evt->button.y, 2 )
					< pow( planets.at(j)->size, 2 )
			) {
				planets.at(j)->focus = true;
				break;
			}
		}
	} else {
		for (unsigned j = 0; j < planets.size(); j++) {
			if (
				// If collision cursor/planet
				pow( planets.at(j)->pos.x - evt->button.x, 2 ) + pow( planets.at(j)->pos.y - evt->button.y, 2 )
					< pow( planets.at(j)->size, 2 )
			) {
				for ( unsigned i = 0; i < ships.size(); i++ ) {
					ships.at(i)->head_to(*planets.at(j));
				}
				break;
			}
		}
	}

}

void Game::onKeyDown( SDL_Event* evt ) {
	keys[ evt->key.keysym.sym ] = 1;
}

void Game::onKeyUp( SDL_Event* evt ) {
	keys[ evt->key.keysym.sym ] = 0;
}

void Game::onMouseUp( SDL_Event* evt ) {
	click = false;
}

void Game::clearPlanetsFocus( SDL_Event* evt )
{
	for (unsigned j = 0; j < planets.size(); j++) {
		planets.at(j)->focus = false;
	}
}
