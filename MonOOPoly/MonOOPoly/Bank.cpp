#include "Bank.h"

void Bank::buyProperty(PropertyField* propertyField, Player* player)
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

void Bank::payRent(Board* board, PropertyField* propertyField, Player* renter)
{
	if (propertyField->getOwner() == nullptr)
	{
		return;
	}

	Player* owner = propertyField->getOwner();

	int renterBalance = renter->getBalance();
	int ownerBalance = owner->getBalance();

	int rent = propertyField->getCurrentRent();

	if (renterBalance >= rent)
	{
		renterBalance -= rent;
		ownerBalance += rent;

		renter->setBalance(renterBalance);

		owner->setBalance(ownerBalance);

		std::cout << "Rent of " << rent << "$ paid!" << std::endl;
		renter->printName();
		std::cout << "'s new balance is "<< renterBalance <<"$" << std::endl;

		owner->printName();
		std::cout << "'s new balance is " << ownerBalance << "$" << std::endl;

	}
	else
	{
		std::cout << "Not enough money to pay rent!" << std::endl;

		std::cout << "You need " << rent - renterBalance << "$ more" << std::endl;
		std::cout << "Sell properties or trade them to players" << std::endl;
		std::cout << "Commands:" << std::endl;
		std::cout << "sell <property index>" << std::endl;

		while (true)
		{
			if (board->getNumberOfPropertiesOwnedByPlayer(renter->getIndex()) <= 0)
			{
				renter->setIsResigned(true);

				std::cout << "Player ";
				renter->printName();
				std::cout << " has bankrupted!" << std::endl;

				break;
			}

			MyString input = "";
			std::cin >> input;

			if (input == "sell")
			{
				int index;
				std::cin >> index;

				Field* field = board->getFieldByIndex(index);

				if (field->getType() == FieldType::Property)
				{
					PropertyField* soldField = static_cast<PropertyField*>(field);

					if (soldField->getOwner() == nullptr || soldField->getOwner()->getIndex() != renter->getIndex())
					{
						renter->printName();
						std::cout << " doesnt own the property"<<std::endl;
					}
					else
					{
						sellProperty(soldField, renter);
					}
				}
				else
				{
					std::cout << "Invalid property" << std::endl;
				}
			}

			renterBalance = renter->getBalance();
			ownerBalance = owner->getBalance();

			int rent = propertyField->getCurrentRent();

			if (renterBalance >= rent)
			{
				payRent(board, propertyField, renter);
				break;
			}

			
		}
	}
}

void Bank::sellProperty(PropertyField* propertyField, Player* player)
{
	if (propertyField->getOwner() == nullptr)
	{
		return;
	}

	if (propertyField->getOwner()->getIndex() != player->getIndex())
	{
		return;
	}

	int price = propertyField->getPrice();
	int balance = player->getBalance();

	std::cout << "Selling property " << propertyField->getName() << 
		" ("<< propertyField->getIndex() <<")" << std::endl;

	balance += price;

	player->setBalance(balance);

	player->printName();
	std::cout << "'s new balance is " <<balance<<"$" << std::endl;
	
	propertyField->setOwner(nullptr);
}
