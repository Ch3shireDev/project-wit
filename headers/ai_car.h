#pragma once
#include "car.h"

class AiCar:public Car
{
public:
	AiCar(double x, double y):Car(x,y)
	{
		
	}

	void update(double dt) override;
	
	int get_pixel_color(double x, double y) override { return 0x0006; }
};
