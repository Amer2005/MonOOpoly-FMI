#include "ResignCommand.h"

void ResignCommand::run(Board* board, Bank* bank) const
{
	int playerIndex = board->getActivePlayerIndex();
	Player* player = board->getPlayerByIndex(playerIndex);

	player->setIsResigned(true);

	std::cout << "Player ";
	player->printName();
	std::cout << " has resigned!" << std::endl;

	board->endTurn();
}
