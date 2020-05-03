#include "display.h"
#include "input.h"
#include "update.h"
#include "objects.h"

class Car : public Object
{

public:
    Car(double x, double y) : Object(x, y) {}

    bool is_playable = true;

    void update(double dt) override
    {
        InputEnum input = get_input();
        if (input == UP_ARROW)
        {
            position.y += 10;
        }
        if (input == DOWN_ARROW)
        {
            position.y -= 10;
        }
        if (input == LEFT_ARROW)
        {
            position.x -= 10;
        }
        if (input == RIGHT_ARROW)
        {
            position.x += 10;
        }
    }
};

int main()
{

    Object *car = new Car(50, 30);

    while (true)
    {
        update();
        show();
        input();
        Sleep(10);
    }
}