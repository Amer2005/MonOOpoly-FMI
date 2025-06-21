#include "Dice.h"

void Dice::init()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

int Dice::rollDice()
{
	return (std::rand() % 6) + 1;
}
