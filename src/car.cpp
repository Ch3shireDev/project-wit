#include "car.h"

#include <cmath>

#include "input.h"
#include "object.h"

Car::Car(double x, double y) : Object(x, y)
{
}


double velocity = 0;

void Car::update(double dt)
{
	double acceleration = 0;
	if (get_input(InputEnum::UP_ARROW))
	{
		acceleration = 100;
	}
	if (get_input(InputEnum::DOWN_ARROW))
	{
		acceleration = -50;
	}
	if (get_input(InputEnum::LEFT_ARROW))
	{
		rotation -= dt * acceleration / 50;
	}
	if (get_input(InputEnum::RIGHT_ARROW))
	{
		rotation += dt * acceleration / 50;
	}

	velocity *= 0.9;
	velocity += acceleration * dt;

	position.x += velocity * sin(rotation) * dt;
	position.y += velocity * cos(rotation) * dt;
}
