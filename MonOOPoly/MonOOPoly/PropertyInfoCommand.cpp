#include "PropertyInfoCommand.h"
#include "ConsoleUtil.h"

void PropertyInfoCommand::run(Board* board, Bank* bank) const
{
	int index;
	std::cin >> index;
	
	if (index < 0 || index >= board->getFieldCount())
	{
		throw std::runtime_error("Invalid index");
	}

	Field* field = board->getFieldByIndex(index);

	if (field->getType() != FieldType::Property)
	{
		throw std::runtime_error("Not a property");
	}

	PropertyField* property = static_cast<PropertyField*>(field);

	std::cout << "price: " << property->getPrice() << std::endl;
	std::cout << "defaultRent: " << property->getDefaultRent() << std::endl;
	std::cout << "cottagePrice: " << property->getCottagePrice() << std::endl;
	std::cout << "castlePrice: " << property->getCastlePrice() << std::endl;

	std::cout << "numberOfCottages: " << property->getNumberOfCottages() << std::endl;
	std::cout << "numberOfCastles: " << property->getNumberOfCastles() << std::endl;

	std::cout << "color: " << property->getColor() << std::endl;

	std::cout << "owner: " << (property->getOwner() ? property->getOwner()->getName() : "No owner") << std::endl;

	ConsoleUtil::waitForAnyInput();
}
