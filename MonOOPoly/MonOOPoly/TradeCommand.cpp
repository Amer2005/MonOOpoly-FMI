#include "TradeCommand.h"

void TradeCommand::run(Board* board, Bank* bank) const
{
	int sellerIndex = board->getActivePlayerIndex();

	Player* seller = board->getPlayerByIndex(sellerIndex);

	int buyerIndex;

	std::cin >> buyerIndex;

	if (buyerIndex < 0 || buyerIndex >= board->getPlayerCount() || buyerIndex == sellerIndex)
	{
		throw std::runtime_error("Invalid player index");
	}

	Player* buyer = board->getPlayerByIndex(buyerIndex);

	int propertyIndex;

	std::cin >> propertyIndex;

	if (propertyIndex < 0 || propertyIndex >= board->getFieldCount())
	{
		throw std::runtime_error("Invalid field index");
	}

	Field* field = board->getFieldByIndex(propertyIndex);

	if (field->getType() != FieldType::Property)
	{
		throw std::runtime_error("Field is not property");
	}

	PropertyField* propertyField = static_cast<PropertyField*>(field);

	if (propertyField->getOwner() == nullptr || propertyField->getOwner()->getIndex() != sellerIndex)
	{
		throw std::runtime_error("You dont own the property");
	}

	int sellValue;

	std::cin >> sellValue;

	if (sellValue < 0)
	{
		throw std::runtime_error("Invalid sell value");
	}

	int sellerBalance = seller->getBalance();
	int buyerBalance = buyer->getBalance();

	if (buyerBalance < sellValue)
	{
		throw std::runtime_error("Buyer doesnt have enough money");
	}

	std::cout << "Player ";
	buyer->printName();
	std::cout << " do you want to buy property "
		<< propertyField->getName() << " (" << propertyField->getIndex() << ")"
		<< " for " << sellValue<<"$?" << std::endl;
	std::cout << "Your current balance: " << buyer->getBalance() << "$" << std::endl;
	std::cout << "y - Accept" << std::endl;
	std::cout << "n - Decline"<<std::endl;

	MyString input = "";

	std::cin >> input;

	if (input == "y")
	{
		sellerBalance += sellValue;
		buyerBalance -= sellValue;

		propertyField->setOwner(buyer);

		buyer->setBalance(buyerBalance);
		seller->setBalance(sellerBalance);
	}
}