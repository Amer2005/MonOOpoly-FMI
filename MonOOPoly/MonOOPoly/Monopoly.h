#pragma once
#include "Board.h"

class Monopoly {
public:
	void run();

	void clearConsole();

	void printTurnMessage(Board* board);

	void mainMenu();
};