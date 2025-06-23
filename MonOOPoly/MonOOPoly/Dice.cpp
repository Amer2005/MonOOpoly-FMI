#include "Dice.h"

void Dice::init()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

int Dice::rollDice()
{
	return generateRandomNumberInclusive(1,6);
}

int Dice::generateRandomNumberInclusive(int min, int max)
{
	return (std::rand() % (max - min + 1)) + min;
}
