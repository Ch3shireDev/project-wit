#include "car.h"

#include <cmath>

#include "input.h"
#include "object.h"
#include "speedway.h"

Car::Car(double x, double y, double width, double height) : Object(x, y)
{
	z_index = 1;
	this->width = width;
	this->height = height;
}


double velocity = 0;

void Car::update(double dt)
{
	double acceleration = 0;
	double rotation_mod = 50;
	
	if (get_input(InputEnum::UP_ARROW))
	{
		acceleration = 150;
	}
	if (get_input(InputEnum::DOWN_ARROW))
	{
		acceleration = -50;
	}
	if (get_input(InputEnum::LEFT_ARROW))
	{
		rotation -= dt * acceleration / rotation_mod;
	}
	if (get_input(InputEnum::RIGHT_ARROW))
	{
		rotation += dt * acceleration / rotation_mod;
	}

	double velocity_mod = 0.95;

	if(speedway!=nullptr && speedway->is_on_track(position)==0)
	{
		velocity_mod = 0.5;
		//if (acceleration > 100)acceleration = 100;
	}
	
	velocity *= velocity_mod;
	velocity += acceleration * dt;

	double dx = position.x - collider->position.x;
	double dy = position.y - collider->position.y;

	if (dx * dx + dy * dy < 10)velocity *= 0.01;
	
	position.x += velocity * sin(rotation) * dt;
	position.y += velocity * cos(rotation) * dt;
}

void Car::set_speedway(Speedway* speedway)
{
	this->speedway = speedway;
}

void Car::set_collider(Car* ai_car)
{
	this->collider = ai_car;
}
