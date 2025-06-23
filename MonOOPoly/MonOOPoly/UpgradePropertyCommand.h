#pragma once
#include "Command.h"

class UpgradePropertyCommand : public Command
{
public:
	void run(Board* board, Bank* bank) const override;
};