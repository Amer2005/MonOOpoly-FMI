#include "Monopoly.h"
#include "Board.h"
#include "Config.h"
#include "Bank.h"
#include "CommandExecutor.h"
#include "Dice.h"
#include "ConsoleUtil.h"

void Monopoly::mainMenu()
{
	std::cout << "Welcome to MonOOpoly" << std::endl;
	std::cout << std::endl;

	std::cout << "Please select an option" << std::endl;

	std::cout << "start <player count> - Start a new game with 2 - 6 players" << std::endl;

	std::cout << "load - Load game from save file" << std::endl;
	std::cout << "exit - Exit the game" << std::endl;
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
	std::cout << "Current balance: " << player->getBalance() << "$" << std::endl;
	std::cout << "Commands: " << std::endl;

	if (!player->getIsInJail())
	{
		std::cout << "roll - Roll the dice and move forward" << std::endl;
		std::cout << "trade <buyer index> <property index> <value> - Offer to sell property to buyer" << std::endl;
		std::cout << "resign - Give up and forfeit the game" << std::endl;
		std::cout << "upgrade <property index> - Add a house/hotel to property" << std::endl;
	}
	else
	{
		std::cout << "roll - Try and get out of jail by getting a pair" << std::endl;
		std::cout << "pay - pay 100$ to get out of jail" << std::endl;
	}

	std::cout << "players - Get info of all players" << std::endl;
	std::cout << "info <property index> - Get info about property" << std::endl;
	std::cout << "exit - Save and exit game" << std::endl;
	std::cout << std::endl;
}

void Monopoly::run()
{
	Dice::init();
	ConsoleUtil::init();

	Board* board = new Board(Config::FieldsFilePath);
	Bank* bank = new Bank();

	mainMenu();

	CommandExecutor* commandExecutor = new CommandExecutor(board, bank);

	while (true)
	{
		MyString input;

		std::cin >> input;

		try
		{
			if (input == "exit")
			{
				board->saveToFile(Config::SaveFilePath);

				break;
			}
			if (input == "load")
			{
				board->loadFromFile(Config::SaveFilePath);
			}
			else
			{
				commandExecutor->executeCommand(input);
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			ConsoleUtil::waitForAnyInput();
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
		
		clearConsole();

		board->print();

		printTurnMessage(board);
	}

	delete board;
	delete bank;
}