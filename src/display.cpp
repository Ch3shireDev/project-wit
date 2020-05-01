#include "display.h"
#include "update.h"
#include "input.h"

void ShowConsoleCursor(bool);

void cls();
void show_screen();

void show()
{
    ShowConsoleCursor(false);
    cls();
    show_screen();
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void cls()
{
    // Get the Win32 handle representing standard output.
    // This generally only has to be done once, so we make it static.
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD topLeft = {0, 0};

    // std::cout uses a buffer to batch writes to the underlying console.
    // We need to flush that to the console because we're circumventing
    // std::cout entirely; after we clear the console, we don't want
    // stale buffered text to randomly be written out.
    std::cout.flush();

    // Figure out the current width and height of the console window
    if (!GetConsoleScreenBufferInfo(hOut, &csbi))
    {
        // TODO: Handle failure!
        abort();
    }
    DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

    DWORD written;

    // Flood-fill the console with spaces to clear it
    FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

    // Reset the attributes of every character to the default.
    // This clears all background colour formatting, if any.
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

    // Move the cursor back to the top left for the next sequence of writes
    SetConsoleCursorPosition(hOut, topLeft);
}

void show_screen()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    string buffer;

    double x = get_pos_x();
    double y = get_pos_y();

    for (int i = 0; i < rows - 1; i++)
    {
        buffer += '\n';
        double Y = (y - i) * (y - i);

        for (int j = 0; j < columns - 1; j++)
        {
            double r = (x - j) * (x - j) + Y;
            if (r < 3)
                buffer += "*";
            else
            {
                buffer += ".";
            }
        }
    }
    fwrite(buffer.c_str(), buffer.length(), 1, stdout);
}
