#include "display.h"
#include "input.h"
#include "update.h"

int main()
{

    while (true)
    {
        update();
        show();
        input();

        // int x = _getch();
        Sleep(10);
    }
}