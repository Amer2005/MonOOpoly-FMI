#pragma once
#include "CardModel.h"
#include "Dice.h"
#include "Config.h"

class GiveMoneyCard : public CardModel
{
	void doAction(Board* board) override;
};