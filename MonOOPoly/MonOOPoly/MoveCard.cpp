#include "MoveCard.h"
#include "Board.h"
#include "Bank.h"

void MoveCard::doAction(Board* board)
{
	int playerIndex = board->getActivePlayerIndex();
	Player* player = board->getPlayerByIndex(playerIndex);

	int newLocation = Dice::generateRandomNumberInclusive(0, board->getFieldCount() - 1);

	std::cout << "You got [Bus] card" << std::endl;

	std::cout << "Moving player to: " << newLocation << std::endl;

	player->setCurrentFieldIndex(newLocation);
}