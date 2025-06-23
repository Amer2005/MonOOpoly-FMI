#pragma once
#include "Command.h"

class PayJailCommand : public Command
{
public:
	void run(Board* board, Bank* bank) const override;
};