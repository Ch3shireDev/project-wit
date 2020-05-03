#include "display.h"
#include "update.h"
#include "input.h"
#include "objects.h"
#include <string>
#include <ctime>

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

char get_pixel_on_pos(vector<Object *>, double, double);

int frames = 0;
int fps = 0;
int last_time = 0;

void show_screen()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    string buffer;

    auto objects = get_all_objects();

    for (int i = 0; i < rows - 1; i++)
    {
        double y = 7 * (rows - i);
        for (int j = 0; j < columns - 1; j++)
        {
            double x = j * 5;
            char pixel = get_pixel_on_pos(objects, x, y);
            buffer += pixel;
        }
        buffer += '\n';
    }
    frames += 1;
    int t = time(0);
    if (t - last_time > 0)
    {
        fps = frames;
        frames = 0;
        last_time = t;
    }
    buffer += std::to_string(fps);
    buffer += "\n";
    fwrite(buffer.c_str(), buffer.length(), 1, stdout);
}

char get_pixel_on_pos(vector<Object *> objects, double x, double y)
{
    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        if ((*it)->is_visible(x, y))
        {
            return '*';
        }
    }

    return ' ';
}