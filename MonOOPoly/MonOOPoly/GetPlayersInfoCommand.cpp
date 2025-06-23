#include "GetPlayersInfoCommand.h"
#include "ConsoleUtil.h"

void GetPlayersInfoCommand::run(Board* board, Bank* bank) const
{
	int playerCount = board->getPlayerCount();

	for (int i = 0; i < playerCount; i++)
	{
		Player* curr = board->getPlayerByIndex(i);

		std::cout << "Player ";
		curr->printName();

		std::cout << " (" << curr->getIndex() << "):"<<std::endl;
		std::cout << "Balance: " << curr->getBalance() << "$" << std::endl;
		std::cout << "Position: " << curr->getCurrentFieldIndex() << std::endl;
		std::cout << "Is in jail: " << (curr->getIsInJail() ? "Yes" : "No") << std::endl;
		std::cout << "Is resigned: " << (curr->getIsResigned() ? "Yes" : "No") << std::endl;

		std::cout << std::endl;
	}

	ConsoleUtil::waitForAnyInput();
}
