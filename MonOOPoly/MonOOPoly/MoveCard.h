#pragma once
#include "CardModel.h"
#include "Dice.h"
#include "Config.h"
class MoveCard : public CardModel
{
	void doAction(Board* board) override;
};