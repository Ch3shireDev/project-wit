#pragma once
#include "object.h"

class Camera : public Object
{
public:

	double camera_margin = 2;
	double camera_scale = 10;

	Object* object;
	Camera(Object* object, double scale=0.1);

	void update(double dt) override;
};
