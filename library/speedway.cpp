#include "speedway.h"

#include <iostream>

double Speedway::get_r2(double x, double y)
{
	double dx = x -position.x;
	double dy = y -position.y;
	return dx * dx + dy * dy;
}

double Speedway::get_r(double x, double y)
{
	return sqrt(get_r2(x, y));
}

bool Speedway::is_pixel_visible(double x, double y)
{
	double R = get_r(x, y);
	return R > r1 && R < r2;
}

char Speedway::get_pixel_type(double x, double y)
{
	double R = get_r(x, y);
	double dr = 2;
	if (R < r1 + dr || R > r2 - dr)return '.';
	return '-';
}

Speedway::Speedway(double x0, double y0, double r1, double dr2): Object(0,0)
{
	this->position = Vec(x0,y0);
	this->r1 = r1;
	this->r2 = r1+dr2;
}