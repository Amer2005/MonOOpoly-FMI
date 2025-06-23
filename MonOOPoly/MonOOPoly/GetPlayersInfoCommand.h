#pragma once
#include "Command.h"

class GetPlayersInfoCommand : public Command
{
public:
	void run(Board* board, Bank* bank) const override;
};