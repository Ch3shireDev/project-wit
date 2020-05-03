#pragma once

enum class InputEnum
{
	NONE,
	UP_ARROW,
	DOWN_ARROW,
	LEFT_ARROW,
	RIGHT_ARROW
};

void input();

bool get_input(InputEnum key);
