#include "CardDeck.h"

void CardDeck::free()
{
	for (int i = 0; i < cardCount; i++)
	{
		delete cards[i];
	}

	delete[] cards;
}

void CardDeck::generateCards()
{
	for (int i = 0; i < cardCount; i++)
	{
		CardModel* curr;

		int rng = Dice::generateRandomNumberInclusive(1, 3);

		if (rng == 1)
		{
			curr = new GiveMoneyCard();
		}
		else if (rng == 2)
		{
			curr = new MoveCard();
		}
		else
		{
			curr = new TakeMoneyCard();
		}

		cards[i] = curr;
	}
}

CardModel* CardDeck::drawCard()
{
	CardModel* card = cards[currentDeckPosition];

	currentDeckPosition++;

	currentDeckPosition = currentDeckPosition % cardCount;

	return card;
}

CardDeck::CardDeck(int numberOfCards)
{
	this->cards = new CardModel*[numberOfCards];

	this->cardCount = numberOfCards;

	generateCards();
}

CardDeck::~CardDeck()
{
	free();
}
