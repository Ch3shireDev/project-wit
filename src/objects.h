#ifndef OBJECTS_H
#define OBJECTS_H

#include <vector>
#include <cmath>

class Object;
void register_object(Object *object);
void unregister_object(Object *object);
std::vector<Object *> get_all_objects();

struct Vec
{
    double x;
    double y;
    Vec() {}
    Vec(double x, double y) {}
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
    double r = 20;

    Object(double x = 0, double y = 0)
    {
        position.x = x;
        position.y = y;
        register_object(this);
    }

    ~Object()
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

    bool is_visible(double x, double y)
    {
        if (distance(x, y) < r)
            return true;
        return false;
    }
};

#endif