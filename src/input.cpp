#include "input.h"
#include "display.h"

InputEnum current_key;

InputEnum get_input()
{
    return current_key;
}

void input()
{
    current_key = NONE;

    if (GetKeyState(VK_UP) & 0x8000)
        current_key = UP_ARROW;
    if (GetKeyState(VK_DOWN) & 0x8000)
        current_key = DOWN_ARROW;
    if (GetKeyState(VK_LEFT) & 0x8000)
        current_key = LEFT_ARROW;
    if (GetKeyState(VK_RIGHT) & 0x8000)
        current_key = RIGHT_ARROW;

    // switch (getch())
    // {
    // case KEY_UP:
    //     current_key = UP_ARROW;
    //     break;
    // case KEY_DOWN:
    //     current_key = DOWN_ARROW;
    //     break;
    // case KEY_RIGHT:
    //     current_key = RIGHT_ARROW;
    //     break;
    // case KEY_LEFT:
    //     current_key = LEFT_ARROW;
    //     break;
    // }
}
