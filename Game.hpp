#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>
#include "Utils.hpp"
#include "Engine.hpp"
#include "Interface.hpp"
#include "Screen.hpp"
#include "Faction.hpp"
#include "Player.hpp"
#include "Entity.hpp"
#include "Planet.hpp"
#include "Star.hpp"
#include "Ship.hpp"

using namespace std;

class Game
{
public:
	Game( Engine* E );
	~Game();
	void start();
	void stop();
	void draw();
	void onQuit();
	void onKeyDown( SDL_Event* event );
	void onKeyUp( SDL_Event* event );
	void onMouseMotion( SDL_Event* event );
	void onMouseDown( SDL_Event* event );
	void onMouseUp( SDL_Event* event );
	void run();
	void update();
private:
	Engine* E;
	Interface* I;
	Screen* screen;
	int target_x;
	int target_y;
	int frameSkip;
	int running;
	int selected_planet;
	bool throttle;
	vector<Faction*> factions;
	vector<Player*> players;
	// vector<Planet*> planets;
	// vector<Ship*> ships;
};

#endif
