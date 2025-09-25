#ifndef Barrricade_h
#define Barricade_h

#include "Arduino.h"

class Barricade {
  public:
    Barricade(int max_width, int max_height, int delayTime);
    void updateBarricade();
    long returnX();
	long returnY();
	int returnDelete();
	int checkColision(int positionxman, int positionyman);
  private:
    long _x;
    long _y;
	int _odelete;
	int _colision;
};

#endif