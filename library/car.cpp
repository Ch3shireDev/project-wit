#include "car.h"

#include <cmath>

#include "input.h"
#include "object.h"

Car::Car(double x, double y, double width, double height) : Object(x, y)
{
	this->width = width;
	this->height = height;
}


double velocity = 0;

void Car::update(double dt)
{
	double acceleration = 0;

	if (get_input(InputEnum::UP_ARROW))
	{
		acceleration = 150;
	}
	if (get_input(InputEnum::DOWN_ARROW))
	{
		acceleration = -5;
	}
	if (get_input(InputEnum::LEFT_ARROW))
	{
		rotation -= dt * acceleration / 30;
	}
	if (get_input(InputEnum::RIGHT_ARROW))
	{
		rotation += dt * acceleration / 30;
	}

	velocity *= 0.9;
	velocity += acceleration * dt;

	position.x += velocity * sin(rotation) * dt;
	position.y += velocity * cos(rotation) * dt;
}
