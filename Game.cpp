#include "Game.hpp"

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

/*
 * Game.cpp
 * Classe noyau du jeu Lightless Sky
 * Auteurs : L. Aubert et T. Borel-Grand
 */

Game::Game( Engine* E )
:E(E), frameSkip(0), running(0), throttle(false) {

	I = new Interface(E);
	screen = new Screen(E);

	factions.push_back(new Faction("Neutre", 255, 0, 255));
	factions.push_back(new Faction("Team 1", 255, 255, 0));

	players.push_back(new Player(E, I, "Monstre", factions.at(0)));
	players.push_back(new Player(E, I, "zM", factions.at(1)));

}

Game::~Game() {
	this->stop();
	for ( unsigned i = 0; i < players.size(); i++ ) {
		delete players.at(i);
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
	if ( E->keys[SDLK_ESCAPE] || ( E->keys[SDLK_F4] && E->keys[SDLK_LALT] ) ) {
		stop();
	}

	for ( unsigned i = 0; i < players.size(); i++ ) {
		players.at(i)->update();
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

	for ( unsigned i = 0; i < players.size(); i++ ) {
		players.at(i)->draw();
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
	E->click = evt->button.button;

	// On diffuse l'événement dans toute l'arborescence
	I->onMouseDown( evt );

	// for (unsigned j = 0; j < players.size(); j++) {
	// 	players.at(j)->onMouseDown( evt );
	// }

	players.at(1)->onMouseDown( evt );

}

void Game::onMouseUp( SDL_Event* evt ) {
	E->click = 0;

	// On diffuse l'événement dans toute l'arborescence
	I->onMouseUp( evt );

	// for (unsigned j = 0; j < players.size(); j++) {
	// 	players.at(j)->onMouseUp( evt );
	// }

	players.at(1)->onMouseUp( evt );
}

void Game::onKeyDown( SDL_Event* evt ) {
	E->keys[ evt->key.keysym.sym ] = 1;

	// Print des infos sur la touche pressée
	printf("Physical %s key acting as %s key | Keycode: %d\n",
      SDL_GetScancodeName(evt->key.keysym.scancode),
      SDL_GetKeyName(evt->key.keysym.sym),
			evt->key.keysym.sym);
}

void Game::onKeyUp( SDL_Event* evt ) {
	E->keys[ evt->key.keysym.sym ] = 0;
}
