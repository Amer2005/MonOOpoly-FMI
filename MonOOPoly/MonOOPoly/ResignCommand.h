#pragma once
#include "Command.h"

class ResignCommand : public Command 
{
public:
	void run(Board* board, Bank* bank) const override;
};