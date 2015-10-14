#include <iostream>
#include "Utils.h"

using namespace std;

Point::Point(int x, int y)
:x(x), y(y) {
}

Point::Point()
:x(NULL), y(NULL) {
}

Point::~Point()
{
}

void Point::_set(int new_x, int new_y)
{
  x = new_x;
  y = new_y;
}

Point Point::operator=(Point p)
{
  x = p.x;
  y = p.y;
}
