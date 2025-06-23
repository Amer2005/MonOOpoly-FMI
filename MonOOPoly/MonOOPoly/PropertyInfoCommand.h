#pragma once
#include "Command.h"

class PropertyInfoCommand : public Command
{
public:
	void run(Board* board, Bank* bank) const override;
};