#pragma once
#include "object.h"

class AiCar;
class Speedway;

class Car : public Object
{
	Speedway* speedway = nullptr;
	Car* collider = nullptr;
public:
	Car(double x, double y, double width = 3, double height = 5);
	void update(double dt) override;
	char get_pixel_type(double x, double y) override { return '*'; }
	int get_pixel_color(double x, double y) override { return 0x0004; }
	void set_speedway(Speedway* speedway);
	void set_collider(Car* ai_car);
};
