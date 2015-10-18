#include <vector>
#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>
#include "SDL2_gfxPrimitives.h"
#include <map>
#include "Utils.h"
#include "Engine.h"
#include "Planet.h"
#include "Ship.h"

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
	std::map<int,int> keys;
	int target_x;
	int target_y;
	int frameSkip;
	int running ;
	bool click;
	vector<Ship*> ships;
	vector<Planet*> planets;
};
