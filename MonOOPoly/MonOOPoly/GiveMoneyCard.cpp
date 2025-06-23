#include "GiveMoneyCard.h"

void GiveMoneyCard::doAction(Board* board, Bank* bank)
{
	int changeAmount = Dice::generateRandomNumberInclusive(0, Config::MoneyChangeMaxCardAmount);

	if (Dice::generateRandomNumberInclusive(0, 1) == 0)
	{
		changeAmount = -changeAmount;
	}

	std::cout << "You got [Stimulus Check] card" << std::endl;

	std::cout << "Your balance changes by " << changeAmount << "$" << std::endl;

	int playerIndex = board->getActivePlayerIndex();
	Player* player = board->getPlayerByIndex(playerIndex);

	int balance = player->getBalance();
	balance += changeAmount;

	if (balance < 0)
	{
		balance = 0;
	}

	std::cout << "New balance is: " << balance << "$" << std::endl;

	player->setBalance(balance);
}
