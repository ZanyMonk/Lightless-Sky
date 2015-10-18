#include "Game.h"
#include "SDL2_gfxPrimitives_font.h"

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

using namespace std;

enum {
	UPDATE_INTERVAL = 1000/60
	, NB_SHIPS = 1
};

Game::Game( Engine* E )
:E(E), frameSkip(0), running(0), click(false) {
	planets.push_back(new Planet(E, Point(500, 200), 20.0));
	planets.push_back(new Planet(E, 900, 400, 40.0));

	for ( int i = 0; i < NB_SHIPS; i++ ) {
		ships.push_back(new Ship(E, *planets[0]));
	}
}

Game::~Game() {
	this->stop();

	for ( int i = 0; i < NB_SHIPS; i++ ) {
		delete ships[i];
	}
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

	if ( keys[SDLK_ESCAPE] || ( keys[SDLK_LALT] && keys[SDLK_F4] ) ) {
		stop();
	}

	for ( unsigned i = 0; i < ships.size(); i++ ) {
		ships.at(i)->update();
	}

}

void Game::draw() {
	// Clear screen
	SDL_SetRenderDrawColor(E->renderer, 25, 25, 25, 255);
	SDL_RenderClear(E->renderer);

	// char str[256];
	//
	// for ( int i = 30; i < 255; i++ ) {
	// 	str[i-30] = i;
	// }
	//
	// str[10] = 30;
	// gfxPrimitivesSetFont(gfxPrimitivesFontdata, 7, 7);
	// stringRGBA(E->renderer, 20, 20, "abcdefghijklmnopqrstuvwxyz", 255, 255, 255, 255);
	// gfxPrimitivesSetFont(gfxPrimitivesFontdata, 8, 8);
	// stringRGBA(E->renderer, 20, 40, str, 255, 255, 255, 255);

	// Draw all planets
	for ( unsigned i = 0; i < planets.size(); i++ ) {
		planets.at(i)->draw();
	}

	// Draw all ships
	for ( unsigned i = 0; i < ships.size(); i++ ) {
		ships.at(i)->draw();
	}

	SDL_RenderPresent(E->renderer);
}

void Game::onMouseMotion( SDL_Event* evt ) {

	// if ( click ) {
	// 	for ( unsigned i = 0; i < ships.size(); i++ ) {
	// 		ships.at(i)->head_to(evt->button.x, evt->button.y);
	// 	}
	// }

	E->cursor._set(evt->button.x, evt->button.y);

}

void Game::onMouseDown( SDL_Event* evt ) {
	click = true;

	for (unsigned j = 0; j < planets.size(); j++) {
		if (
			// If collision cursor/planet
			pow( planets.at(j)->pos.x - evt->button.x, 2 ) + pow( planets.at(j)->pos.y - evt->button.y, 2 )
				< pow( planets.at(j)->size, 2 )
		) {
			for ( unsigned i = 0; i < ships.size(); i++ ) {
				ships.at(i)->head_to(*planets.at(j));
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
