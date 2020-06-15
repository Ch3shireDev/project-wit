#pragma once
#include "object.h"

class Car : public Object
{
public:
	Car(double x, double y, double width = 3, double height = 5);
	void update(double dt) override;
	char get_pixel_type(double x, double y) override { return '*'; }
};
