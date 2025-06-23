#include "MoveCard.h"


void MoveCard::doAction(Board* board, Bank* bank)
{
	int playerIndex = board->getActivePlayerIndex();
	Player* player = board->getPlayerByIndex(playerIndex);

	int newLocation = Dice::generateRandomNumberInclusive(0, board->getFieldCount() - 1);

	std::cout << "You got [Bus] card" << std::endl;

	std::cout << "Moving player to: " << newLocation << std::endl;

	player->setCurrentFieldIndex(newLocation);
}