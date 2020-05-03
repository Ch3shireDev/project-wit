#ifndef INPUT_H
#define INPUT_H

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77


enum InputEnum
{
    NONE,
    UP_ARROW,
    DOWN_ARROW,
    LEFT_ARROW,
    RIGHT_ARROW,
};

void input();
InputEnum get_input();

#endif