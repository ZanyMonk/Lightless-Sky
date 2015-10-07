#include "Engine.h"
#include "Planet.h"
#include "Ship.h"

class Game
{
public:
	Game( Engine E );
	~Game();
	void start();
	void stop();
	void draw();
	void fillRect( SDL_Rect* rc, int r, int g, int b );
	void fpsChanged( int fps );
	void onQuit();
	void onKeyDown( SDL_Event* event );
	void onKeyUp( SDL_Event* event );
	void onMouseDown( SDL_Event* event );
	void onMouseUp( SDL_Event* event );
	void run();
	void update();
private:
	Engine E;
	std::map<int,int> keys;
	int target_x;
	int target_y;
	int frameSkip;
	int running ;
	bool click;
	Ship hero;
	// Ship ship[100];
};