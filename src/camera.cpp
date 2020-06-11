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

Camera::Camera(Object* object)
{
	this->object = object;
	is_visible = false;
}
