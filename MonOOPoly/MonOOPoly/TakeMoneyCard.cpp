#include "TakeMoneyCard.h"
#include "Board.h"

void TakeMoneyCard::doAction(Board* board)
{
	int playerIndex = board->getActivePlayerIndex();
	Player* player = board->getPlayerByIndex(playerIndex);

	int takeAmount = Config::TakeMoneyAmount;

	std::cout << "You got [Steal] card" << std::endl;
	std::cout << "Taking " << takeAmount << "$ from every player!" << std::endl;

	int playerCount = board->getPlayerCount();

	int totalTaken = 0;

	for (int i = 0; i < playerCount; i++)
	{
		Player* curr = board->getPlayerByIndex(i);

		int currTaken = takeAmount;

		if (curr->getIndex() == playerIndex || curr->getIsResigned())
		{
			continue;
		}

		int currentBalance = curr->getBalance();
		currentBalance -= takeAmount;

		if (currentBalance < 0)
		{
			currentBalance = 0;
			currTaken = curr->getBalance();
		}

		curr->setBalance(currentBalance);
		totalTaken += currTaken;
	}

	std::cout << "Total taken amount is " << totalTaken << "$" << std::endl;

	int balance = player->getBalance();

	balance += totalTaken;

	player->setBalance(balance);

	std::cout << "New balance is " << balance << "$" << std::endl;
}
