#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <stdlib.h>
#include <time.h>

class Point {
public:
  Point ( int x, int y );
  Point ();
  ~Point ();
  void _set ( int new_x, int new_y );
  Point operator= ( Point p );

  int x, y;
private:
};

static int random(int a, int b=0)
{
  return rand()%(a-b)+a;
}

#endif
