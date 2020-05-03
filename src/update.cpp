#include "update.h"
#include "objects.h"

void update()
{
    double dt = 0.1;

    std::vector<Object *> objects = get_all_objects();
    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        (*it)->update(dt);
    }
}
