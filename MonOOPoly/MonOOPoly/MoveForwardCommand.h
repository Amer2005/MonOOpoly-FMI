#pragma once
#include "Command.h"

class MoveForwardCommand : public Command
{
private:
	void rollDice(Board* board, Bank* bank, Player* player, int numberOfRolls) const;

	void goToJail(Board* board, Bank* bank, Player* player) const;

	void landOnProperty(Board* board, Bank* bank, Player* player, Field* field) const;
public:
	void run(Board* board, Bank* bank) const override;
};