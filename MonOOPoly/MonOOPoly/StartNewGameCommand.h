#pragma once
#include "Command.h"

class StartNewGameCommand : public Command 
{
public:
	void run(Board* board, Bank* bank) const override;
};