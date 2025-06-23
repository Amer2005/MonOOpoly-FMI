#pragma once
#include "Board.h"
#include "Bank.h"

class CardModel
{
public:
	virtual void doAction(Board* board, Bank* bank);
};