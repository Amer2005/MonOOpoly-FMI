#pragma once
#include "Command.h"

class TradeCommand : public Command
{
public:
	void run(Board* board, Bank* bank) const override;
};