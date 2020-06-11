#include "display.h"
#include "object.h"
#include <string>
#include <ctime>
#include <iostream>
#include <windows.h>

using namespace std;

void ShowConsoleCursor(bool);
void show_screen(Object* camera, int = 120, int = 30);

void show(Object* player)
{
	ShowConsoleCursor(false);
	show_screen(player);
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

char get_pixel_on_pos(vector<Object*>, double, double);

int frames = 0;
int fps = 0;
int last_time = 0;

void show_screen(Object* camera, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	ios_base::sync_with_stdio(false);
	auto objects = get_all_objects();

	Vec pos = camera->get_position();
	string buff2;

	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		double y = pos.y + 8 * (SCREEN_HEIGHT - i) - 4 * SCREEN_HEIGHT;
		for (int j = 0; j < SCREEN_WIDTH; j++)
		{
			double x = pos.x + j * 5 - 5 * SCREEN_WIDTH / 2;
			buff2 += get_pixel_on_pos(objects, x, y);
		}
		buff2 += '\n';
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
	buff2[(SCREEN_HEIGHT - 1) * (SCREEN_WIDTH + 1)] = fps_str[0];
	if (fps_str.length() > 1)
	{
		buff2[(SCREEN_HEIGHT - 1) * (SCREEN_WIDTH + 1) + 1] = fps_str[1];
	}

	fwrite(buff2.c_str(), buff2.length(), 1, stderr);
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
