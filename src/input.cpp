#include "input.h"
#include "display.h"


double x, y;

double get_pos_x() { return x; }
double get_pos_y() { return y; }
void set_pos_x(double x0) { x = x0; }
void set_pos_y(double y0) { y = y0; }
void change_pos_x(double dx) { x = x + dx; }
void change_pos_y(double dy) { y = y + dy; }

void input()
{
    if (GetKeyState(VK_UP) & 0x8000 /*Check if high-order bit is set (1 << 15)*/)
    {
        change_pos_y(-0.5);

        // Do stuff
    }

    if (GetKeyState(VK_DOWN) & 0x8000 /*Check if high-order bit is set (1 << 15)*/)
    {
        change_pos_y(0.5);

        // Do stuff
    }

    if (GetKeyState(VK_LEFT) & 0x8000 /*Check if high-order bit is set (1 << 15)*/)
    {
        change_pos_x(-1);

        // Do stuff
    }

    if (GetKeyState(VK_RIGHT) & 0x8000 /*Check if high-order bit is set (1 << 15)*/)
    {
        change_pos_x(+1);

        // Do stuff
    }
}