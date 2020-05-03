#define WIN32_LEAN_AND_MEAN
#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 30

#include "display.h"
#include "object.h"
#include <string>
#include <ctime>
#include <iostream>
#include <windows.h>

using namespace std;
void ShowConsoleCursor(bool);

void show_screen(Object* camera);
void cls();

void show(Object* player)
{
	ShowConsoleCursor(false);
	cls();
	show_screen(player);
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

char get_pixel_on_pos(vector<Object*>, double, double);

int frames = 0;
int fps = 0;
int last_time = 0;


void show_screen_old()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	string buffer;

	auto& objects = get_all_objects();

	for (auto i = 0; i < rows - 1; i++)
	{
		const auto y = static_cast<double>(rows - i) * 7;
		for (auto j = 0; j < columns - 1; j++)
		{
			const auto x = 5 * static_cast<double>(j);
			const auto pixel = get_pixel_on_pos(objects, x, y);
			buffer += pixel;
		}
		buffer += '\n';
	}
	frames += 1;
	const int t = time(nullptr);
	if (t - last_time > 0)
	{
		fps = frames;
		frames = 0;
		last_time = t;
	}
	buffer += std::to_string(fps);
	buffer += "\n";
	fwrite(buffer.c_str(), buffer.length(), 1, stderr);
}


auto hOutput = static_cast<HANDLE>(GetStdHandle(STD_OUTPUT_HANDLE));

COORD dwBufferSize = {SCREEN_WIDTH,SCREEN_HEIGHT};
COORD dwBufferCoord = {0, 0};
SMALL_RECT rcRegion = {0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1};

CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];


void show_screen(Object* camera)
{
	ios_base::sync_with_stdio(false);
	auto objects = get_all_objects();

	ReadConsoleOutput(hOutput, reinterpret_cast<CHAR_INFO*>(buffer), dwBufferSize,
	                  dwBufferCoord, &rcRegion);

	Vec pos = camera->get_position();

	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		double y = pos.y + 8 * (SCREEN_HEIGHT - i) - 4 * SCREEN_HEIGHT;
		for (int j = 0; j < SCREEN_WIDTH; j++)
		{
			double x = pos.x + j * 5 - 5 * SCREEN_WIDTH / 2;
			buffer[i][j].Char.AsciiChar = get_pixel_on_pos(objects, x, y);
		}
	}

	frames += 1;
	int t = time(nullptr);
	if (t - last_time > 0)
	{
		fps = frames;
		frames = 0;
		last_time = t;
	}

	string fps_str = to_string(fps);
	buffer[SCREEN_HEIGHT - 1][0].Char.AsciiChar = fps_str[0];
	if (fps_str.length() > 1)
		buffer[SCREEN_HEIGHT - 1][1].Char.AsciiChar = fps_str[1];


	WriteConsoleOutput(hOutput, reinterpret_cast<CHAR_INFO*>(buffer), dwBufferSize,
	                   dwBufferCoord, &rcRegion);
	Sleep(16);
}


char get_pixel_on_pos(vector<Object*> objects, double x, double y)
{
	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		if ((*it)->is_pixel_visible(x, y))
		{
			return '*';
		}
	}

	return ' ';
}
