#pragma once


class Board;

class CardModel
{
public:
	virtual void doAction(Board* board);
};