#pragma once
#include "PropertyField.h"
#include "Board.h"
class Bank
{
private:

public:
	void buyProperty(PropertyField* propertyField, Player* player);

	void payRent(Board* board, PropertyField* propertyField, Player* renter);

	void sellProperty(PropertyField* propertyField, Player* player);
};