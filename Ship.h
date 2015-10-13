#ifndef SHIP_H
#define SHIP_H
#include "Engine.h"

class Ship
{
public:
	Ship( Engine E );
	~Ship();
	void draw();
	void update();
	void head_to(int x, int y);
	void gravitate();
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
