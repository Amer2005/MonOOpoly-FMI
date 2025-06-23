#pragma once
#include "CardModel.h"
#include "Dice.h"
#include "Config.h"

class TakeMoneyCard : public CardModel
{
	void doAction(Board* board, Bank* bank) override;
};