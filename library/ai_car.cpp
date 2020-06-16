#include "ai_car.h"

double t = 0;

void AiCar::update(double dt) 
{
	t += dt;
	
	double R = 1020;
	double x0 = -R+18;
	double y0 = 0;
	double T = 10.5;

	double t2 = t - 3;
	if (t2 < 0)t2 = 0;

	double x = x0+ R* cos(t2 / T);
	double y = y0+ R* sin(t2 / T);

	this->position.x = x;
	this->position.y = y;

	this->rotation = -t2 / T;
}
