#include "ConsoleUtil.h"

HANDLE ConsoleUtil::hConsole;

void ConsoleUtil::init()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void ConsoleUtil::setConsoleColor(ColorType color)
{
	SetConsoleTextAttribute(hConsole, getConsoleColorCode(color));
}

int ConsoleUtil::getConsoleColorCode(ColorType color)
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
	case JailColor:
		return (BACKGROUND_RED |
			FOREGROUND_GREEN | FOREGROUND_RED  | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	case GoToJailColor:
		return (BACKGROUND_RED | BACKGROUND_GREEN |
			FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	case DrawCardColor:
		return (BACKGROUND_RED | BACKGROUND_BLUE |
			FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	case ParkingColor:
		return ( BACKGROUND_BLUE |
			FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	case StartColor:
		return (BACKGROUND_GREEN |
			FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	default:
		return 15;
	}
}

void ConsoleUtil::waitForAnyInput()
{
	system("pause");
	//std::cout << "Type anything to continue" << std::endl;
	//MyString input = "";
	//std::cin >> input;
}