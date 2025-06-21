#include "ConsoleColor.h"

HANDLE ConsoleColor::hConsole;

void ConsoleColor::init()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void ConsoleColor::setConsoleColor(ColorType color)
{
	SetConsoleTextAttribute(hConsole, getConsoleColorCode(color));
}

int ConsoleColor::getConsoleColorCode(ColorType color)
{
	switch (color)
	{
	case Default:
		return 15;
	case Player1:
		return 10;
	case Player2:
		return 11;
	case Player3:
		return 12;
	case Player4:
		return 13;
	case Player5:
		return 14;
	case Player6:
		return 8;
	default:
		return 15;
	}
}