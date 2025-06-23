#pragma once
#include "CardModel.h"
#include "Dice.h"

#include "TakeMoneyCard.h"
#include "GiveMoneyCard.h"
#include "MoveCard.h"

class CardDeck
{
private:
	CardModel** cards;

	int cardCount;

	int currentDeckPosition = 0;

	void free();

	void generateCards();
public:
	CardDeck(int numberOfCards);

	void drawCard(Board* board, Bank* bank);

	~CardDeck();
};