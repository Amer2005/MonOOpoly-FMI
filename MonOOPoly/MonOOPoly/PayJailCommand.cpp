#include "PayJailCommand.h"
#include "Config.h"
#include "ConsoleUtil.h"

void PayJailCommand::run(Board* board, Bank* bank) const
{
	int playerIndex = board->getActivePlayerIndex();
	Player* player = board->getPlayerByIndex(playerIndex);

	int balance = player->getBalance();

	if(balance < Config::JailBailCost)
	{
		throw std::runtime_error("Not enough money to pay bail");
	}

	balance -= Config::JailBailCost;

	player->setIsInJail(false);

	std::cout << "You got out of jail!"<<std::endl;

	board->endTurn();

	ConsoleUtil::waitForAnyInput();

	return;
}
