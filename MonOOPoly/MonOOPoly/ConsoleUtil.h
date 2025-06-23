#pragma once
#include <windows.h>
#undef max
#undef min
#include "ColorType.h"

class ConsoleUtil
{
private:
	static HANDLE hConsole;

public:
	void static init();

	void static setConsoleColor(ColorType color);

	int static getConsoleColorCode(ColorType color);

	void static waitForAnyInput();
};