#pragma once
#include <cstdlib>
#include <ctime>

class Dice {
public:
	static void init();

	static int rollDice();

	static int generateRandomNumberInclusive(int min, int max);
};