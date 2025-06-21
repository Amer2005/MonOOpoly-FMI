#pragma once
#include "Board.h"
#include "Bank.h"
class Command {
public:
	virtual void run(Board* board, Bank* bank) const = 0;
};