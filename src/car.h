#pragma once
#include "object.h"

class Car : public Object
{
public:
	Car(double x, double y);
	void update(double dt) override;
};
