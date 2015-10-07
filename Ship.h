#ifndef SHIP_H
#define SHIP_H
#include "Engine.h"

class Ship
{
public:
	Ship( Engine E );
	~Ship();
	void draw();
	void fillRect(SDL_Rect* rc, int r, int g, int b);
	void move_to(int x, int y);
	int get_faction();
	bool is_traveling();
	Engine E;
	int dep_x, dep_y;
	int x, y;
	int size;
private:
	int _health;
	int _faction;
	bool _is_traveling;
};

#endif