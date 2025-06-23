#include "UpgradePropertyCommand.h"
#include "Config.h"
#include "ConsoleUtil.h"

void UpgradePropertyCommand::run(Board* board, Bank* bank) const
{
	int playerIndex = board->getActivePlayerIndex();
	Player* player = board->getPlayerByIndex(playerIndex);

	int propertyIndex;
	std::cin >> propertyIndex;

	if (propertyIndex < 0 || propertyIndex >= board->getFieldCount())
	{
		throw std::runtime_error("Invalid property index");
	}

	Field* field = board->getFieldByIndex(propertyIndex);

	if (field->getType() != FieldType::Property)
	{
		throw std::runtime_error("Field is not a property");
	}

	PropertyField* propertyField = static_cast<PropertyField*>(field);

	if (propertyField->getOwner() == nullptr || propertyField->getOwner()->getIndex() != player->getIndex())
	{
		throw std::runtime_error("Property not owned by player");
	}

	if (!board->doesPlayerOwnAllPropertiesOfColor(playerIndex, propertyField->getColor()))
	{
		throw std::runtime_error("You need to own all properties of color to upgrade them");
	}

	int playerBalance = player->getBalance();

	int numberOfCottages = propertyField->getNumberOfCottages();
	int numberOfCastles = propertyField->getNumberOfCastles();
	int price = 0;

	if (numberOfCottages < Config::MaxNumberOfCottages)
	{
		price = propertyField->getCottagePrice();
		numberOfCottages++;
	}
	else if (numberOfCastles < Config::MaxNumberOfCastles)
	{
		price = propertyField->getCastlePrice();
		numberOfCastles++;
	}
	else
	{
		throw std::runtime_error("Property is already fully upgraded");
	}

	if (playerBalance < price)
	{
		throw std::runtime_error("Not enough money to upgrade");
	}

	playerBalance -= price;

	player->setBalance(playerBalance);
	propertyField->setNumberOfCottages(numberOfCottages);
	propertyField->setNumberOfCastles(numberOfCastles);

	std::cout << "Upgraded property!" << std::endl;

	ConsoleUtil::waitForAnyInput();
}
