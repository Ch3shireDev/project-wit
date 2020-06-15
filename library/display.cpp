#include "display.h"
#include "object.h"
#include <string>
#include <ctime>
#include <iostream>
#include <windows.h>

#include "camera.h"

using namespace std;

void ShowConsoleCursor(bool);
void show_screen(Camera* camera);

void show(Camera* camera)
{
	ShowConsoleCursor(false);
	show_screen(camera);
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

char get_pixel_symbol_on_pos(vector<Object*>, double, double);
int get_pixel_color_on_pos(const vector<Object*>& vector, double x, double y);

int frames = 0;
int fps = 0;
time_t last_time = 0;


auto hOutput = static_cast<HANDLE>(GetStdHandle(STD_OUTPUT_HANDLE));

const int SCREEN_WIDTH = 120;
const int SCREEN_HEIGHT = 30;

COORD dwBufferSize = {SCREEN_WIDTH, SCREEN_HEIGHT};
COORD dwBufferCoord = {0, 0};
SMALL_RECT rcRegion = {0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1};
CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

void show_screen(Camera* camera)
{
	ios_base::sync_with_stdio(false);

	auto objects = get_all_objects();

	ReadConsoleOutput(hOutput, reinterpret_cast<CHAR_INFO*>(buffer), dwBufferSize,
	                  dwBufferCoord, &rcRegion);

	Vec pos = camera->get_position();
	//string buff2;

	double width_unit = 5 / camera->camera_scale;
	double height_unit = 12 / camera->camera_scale;


	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		double y = pos.y + height_unit * (SCREEN_HEIGHT*1. - i*1.) - height_unit * SCREEN_HEIGHT / 2.;
		for (int j = 0; j < SCREEN_WIDTH; j++)
		{
			double x = pos.x + j * width_unit - width_unit * SCREEN_WIDTH / 2;
			char pixel = get_pixel_symbol_on_pos(objects, x, y);
			int color = get_pixel_color_on_pos(objects, x, y);
			//buff2 += pixel;
			buffer[i][j].Char.AsciiChar = pixel;
			buffer[i][j].Attributes = color;
		}
		//buff2 += '\n';
	}

	frames += 1;
	time_t t = time(nullptr);
	if (t - last_time > 0)
	{
		fps = frames;
		frames = 0;
		last_time = t;
	}

	string fps_str = to_string(fps);
	//buff2[(SCREEN_HEIGHT - 1) * (SCREEN_WIDTH + 1)] = fps_str[0];
	//if (fps_str.length() > 1)
	//{
	//	buff2[(SCREEN_HEIGHT - 1) * (SCREEN_WIDTH + 1) + 1] = fps_str[1];
	//}

	buffer[SCREEN_HEIGHT - 1][0].Char.AsciiChar = fps_str[0];
	if (fps_str.length() > 1)
		buffer[SCREEN_HEIGHT - 1][1].Char.AsciiChar = fps_str[1];

	//fwrite(buff2.c_str(), buff2.length(), 1, stderr);
	WriteConsoleOutput(hOutput, reinterpret_cast<CHAR_INFO*>(buffer), dwBufferSize, dwBufferCoord, &rcRegion);
}

char get_pixel_symbol_on_pos(vector<Object*> objects, double x, double y)
{
	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		if ((*it)->is_pixel_visible(x, y))
		{
			return (*it)->get_pixel_type(x, y);
		}
	}
	return ' ';
}

int get_pixel_color_on_pos(const vector<Object*>& objects, double x, double y)
{
	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		if ((*it)->is_pixel_visible(x, y))
		{
			//return 0;
			return (*it)->get_pixel_color(x, y);
		}
	}
	return 0;
}
