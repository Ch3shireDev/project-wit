#pragma once
#include <vector>
#include <cmath>

class Object;
void register_object(Object* object);
void unregister_object(Object* object);
std::vector<Object*>& get_all_objects();

struct Vec
{
	double x = 0;
	double y = 0;

	Vec()
	{
	}

	Vec(double x, double y) :x(x), y(y)
	{
	}
};

class Object
{
protected:
	Vec position;
	double velocity_x;
	double velocity_y;
	double force_x;
	double force_y;

public:
	double rotation = 0;

	double width = 2;
	double height = 4;

	bool is_visible = true;
	bool is_static = false;

	int z_index = 0;
	
	Object(double x = 0, double y = 0)
	{
		position.x = x;
		position.y = y;
		register_object(this);
	}

	virtual ~Object()
	{
		unregister_object(this);
	}

	virtual void update(double dt)
	{
	}

	Vec get_position()
	{
		return position;
	}

	double distance(double x, double y)
	{
		double dx = x - position.x;
		double dy = y - position.y;
		return sqrt(dx * dx + dy * dy);
	}

	virtual bool is_pixel_visible(double x, double y)
	{
		if (!is_visible)return false;

		double dx = position.x - x;
		double dy = position.y - y;

		double dx2 = cos(rotation) * dx - sin(rotation) * dy;
		double dy2 = sin(rotation) * dx + cos(rotation) * dy;

		if (abs(dx2) > width / 2)return false;
		if (abs(dy2) > height / 2)return false;
		return true;
	}

	virtual char get_pixel_type(double x, double y) { return '*'; }
};