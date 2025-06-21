#include "StartNewGameCommand.h"
#include "Config.h"

void StartNewGameCommand::run(Board* board, Bank* bank) const
{
	int playerCount;

	std::cin >> playerCount;

	if (!std::cin.good())
	{
		throw std::runtime_error("Invalid input");
	}

	if (playerCount < Config::MinPlayers || playerCount > Config::MaxPlayers)
	{
		throw std::runtime_error("Please enter a valid player count!");
	}

	MyString** names = new MyString* [playerCount] {nullptr};

	for (int i = 0; i < playerCount; i++)
	{
		std::cout << "Enter Player " <<i + 1<<  " name: ";
		MyString input;
		std::cin >> input;

		names[i] = new MyString();

		*names[i] = input;
	}

	board->setPlayers(names, playerCount);
}