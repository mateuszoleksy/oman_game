#include "Arduino.h"
#include "Barricade.h"

Barricade::Barricade (int max_width, int max_height, int delayTime) {
	if (max_width!=0) {
		_x = max_width + random(0, 5);
		_y = random(0, 2);
		if (_y==1){
		_y=25;
		} else
			_y=0;
		_odelete = 0; // if delate equals 1 object must be delate
		_colision = 0;
	}
	else {
		_x = NULL;
		_y = NULL;
		_odelete = 1;
		_colision = 0;
	}
}

void Barricade::updateBarricade () {
	if (_odelete!=1)
		_x-=10;
	if (_x<=0)
		_odelete = 1;
}

long Barricade::returnX () {
	return _x;
}

long Barricade::returnY () {
	return _y;
}

int Barricade::returnDelete () {
	return _odelete;
}

int Barricade::checkColision (int positionxman, int positionyman) {
	if (_x+5 >= positionxman && _x-5 <= positionxman) {
		if (_y == positionyman)
			_colision = 1;
	}
	return _colision;
}