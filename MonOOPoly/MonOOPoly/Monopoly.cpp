#include "Monopoly.h"
#include "Board.h"
#include "Config.h"
#include "Bank.h"
#include "CommandExecutor.h"
#include "Dice.h"
#include "ConsoleColor.h"

void Monopoly::mainMenu()
{
	std::cout << "Welcome to MonOOpoly" << std::endl;
	std::cout << std::endl;

	std::cout << "Please select an option" << std::endl;

	std::cout << "start <player count> - Start a new game with 2 - 6 players" << std::endl;

	std::cout << "load - Load game from save file" << std::endl;
}

void Monopoly::clearConsole()
{
	system("cls");
}

void Monopoly::printTurnMessage(Board* board)
{
	int playerIndex = board->getActivePlayerIndex();

	Player* player = board->getPlayerByIndex(playerIndex);

	std::cout << "Player ";

	player->printName();

	std::cout << "'s turn" << std::endl;
	std::cout << "Current position: " << player->getCurrentFieldIndex() << std::endl;
	std::cout << "Valid commands: " << std::endl;
	std::cout << "roll - roll the dice and move forward" << std::endl;
	std::cout << "trade <player name> <property index> <value> - offer to sell property to player" << std::endl;
	std::cout << "resign - give up and forfeit the game" << std::endl;
}

void Monopoly::run()
{
	Dice::init();
	ConsoleColor::init();

	Board* board = new Board(Config::SaveFilePath);
	Bank* bank = new Bank();

	CommandExecutor* commandExecutor = new CommandExecutor(board, bank);
	
	mainMenu();

	while (true)
	{
		MyString input;

		bool exception = false;

		std::cin >> input;

		try
		{
			commandExecutor->executeCommand(input);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
			exception = true;
		}

		if (board->getIsGameOver())
		{
			int playerIndex = board->getActivePlayerIndex();

			Player* player = board->getPlayerByIndex(playerIndex);

			std::cout << "Player ";

			player->printName();

			std::cout << " won the game!" << std::endl;

			break;
		}

		if (!exception)
		{
			clearConsole();
		}


		board->print();

		printTurnMessage(board);
	}
}