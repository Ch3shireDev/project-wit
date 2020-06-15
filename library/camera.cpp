#include "camera.h"

#include <cmath>

void Camera::update(double dt)
{
	Vec pos = object->get_position();
	double dx = pos.x - position.x;
	double dy = pos.y - position.y;

	if (abs(dx) > camera_margin)
	{
		position.x += dx / 5;
	}

	if (abs(dy) > camera_margin)
	{
		position.y += dy / 5;
	}
}

Camera::Camera(Object* object, double scale)
{
	this->camera_scale = scale;
	this->object = object;
	is_visible = false;
}
