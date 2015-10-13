#ifndef SHIP_H
#define SHIP_H
#include "Engine.h"

class Ship
{
public:
	Ship( Engine E );
	~Ship();
	void draw();
<<<<<<< HEAD
	void update();
	void head_to(int x, int y);
	void gravitate();
=======
	void fillRect(SDL_Rect* rc, int r, int g, int b);
	void move_to(int target_x, int target_y);
>>>>>>> fc98453b2e7a21d0323b773cd4bf0e6ab14b9dfb
	int get_faction();
	bool is_traveling();
	Engine E;
	int target_x, target_y;
	int x, y;
	int size;
	double speed;
	bool _is_traveling;
private:
	int _health;
	int _faction;
};

#endif
