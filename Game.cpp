#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <math.h>
#include <map>
#include "Game.h"

using namespace std;

enum {
	DISPLAY_WIDTH  = 480
	, DISPLAY_HEIGHT = 320
	, UPDATE_INTERVAL = 1000/60
	, HERO_SPEED = 10

};

bool is_traveling = false;

Game::Game( Engine E )
:E(E), frameSkip(0), running(0), click(false), hero(E) {
}

Game::~Game() {
	this->stop();
}

void Game::start() {
	this->running = 1;
	run();
}

void Game::draw() {
	// Clear screen
	SDL_SetRenderDrawColor(E.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(E.renderer);

	hero.draw();

	SDL_RenderPresent(E.renderer);
}

void Game::stop() {
	onQuit();
	running = 0;
	if (NULL != E.renderer) {
		SDL_DestroyRenderer(E.renderer);
		E.renderer = NULL;
	}
	if (NULL != E.window) {
		SDL_DestroyWindow(E.window);
		E.window = NULL;
	}
	SDL_Quit();
}

void Game::fillRect(SDL_Rect* rc, int r, int g, int b) {
	SDL_SetRenderDrawColor(E.renderer, r, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(E.renderer, rc);
}

// void Game::fpsChanged( int fps ) {
// 	char szFps[ 128 ];
// 	SDL_SetWindowTitle(E.window, szFps);
// }

//---
//- Appelé quand l'événement Quit est activé
void Game::onQuit()
{

}

//---
//- Main loop
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
				case SDL_MOUSEBUTTONDOWN: onMouseDown( &event );  break;
				case SDL_MOUSEBUTTONUP:   onMouseUp( &event );    break;
				case SDL_MOUSEMOTION: break;
			}
		}
		// update/draw
		timeElapsed = (now=SDL_GetTicks()) - past;
		if ( timeElapsed >= UPDATE_INTERVAL  ) {
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
			// fpsChanged( fps );
			fps = 0;
		}
		// sleep?
		SDL_Delay( 9 );
	}
}

void Game::onMouseDown( SDL_Event* evt ) {
	click = true;
	is_traveling = 1;
	hero.dep_x = hero.x;
	hero.dep_y = hero.y;
	posvaleur=0;
	targetsupx=0;

	target_x = evt->button.x;
	target_y = evt->button.y;
}

void Game::update() {

	if ( keys[SDLK_LEFT] && hero.x > 0 ) {
		hero.x -= HERO_SPEED;
	} else if ( keys[SDLK_RIGHT] && (hero.x + hero.size) < E.display.w ) {
		hero.x += HERO_SPEED;
	}
	if ( keys[SDLK_UP] && hero.y > 0 ) {
		hero.y -= HERO_SPEED;
	} else if ( keys[SDLK_DOWN] && (hero.y + hero.size) < E.display.h ) {
		hero.y += HERO_SPEED;
	}

	if ( is_traveling ) {
		//calcul distance
		double Dist_x = (target_x)-(hero.x) ;
		double Dist_y = (target_y)-(hero.y) ;

		double Radian = atan2(Dist_y,Dist_x);

		hero.x += (cos(Radian)*HERO_SPEED);
		hero.y += (sin(Radian)*HERO_SPEED);

		//Test fin de course
		if ( (hero.x==target_x) && (hero.y==target_y) )  {

			is_traveling = 0;
			hero.x=target_x;
			hero.y=target_y;
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
