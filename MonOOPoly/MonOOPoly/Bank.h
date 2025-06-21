#pragma once
#include "PropertyField.h"
class Bank
{
private:

public:
	void BuyProperty(PropertyField* propertyField, Player* player)
	{
		int price = propertyField->getPrice();
		int balance = player->getBalance();

		if (balance < price)
		{
			return;
		}

		propertyField->setOwner(player);

		balance -= price;

		player->setBalance(balance);
	}
};