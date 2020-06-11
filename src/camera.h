#pragma once
#include "object.h"

class Camera : public Object
{
public:

	double camera_margin = 20;

	Object* object;
	Camera(Object* object);

	void update(double dt) override;
};
