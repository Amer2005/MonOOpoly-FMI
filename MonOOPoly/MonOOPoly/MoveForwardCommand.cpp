#include "MoveForwardCommand.h"
#include "Dice.h"
#include "PropertyField.h"
void MoveForwardCommand::run(Board* board, Bank* bank) const
{
	int activePlayerIndex = board->getActivePlayerIndex();
	Player* player = board->getPlayerByIndex(activePlayerIndex);

	this->rollDice(board, bank, player, 1);
}

void MoveForwardCommand::rollDice(Board* board, Bank* bank, Player* player, int numberOfRolls) const
{
	int* dice = new int[2];

	dice[0] = Dice::rollDice();
	dice[1] = Dice::rollDice();

	std::cout << "Dice rolls: " << dice[0] << " " << dice[1] << std::endl;

	if (numberOfRolls >= 3 && dice[0] == dice[1])
	{
		std::cout << "CHEATER! You go to jail" << std::endl;

		goToJail(board, bank, player);

		return;
	}

	int totalRolled = dice[0] + dice[1];

	int playerPosition = player->getCurrentFieldIndex();

	playerPosition += totalRolled;

	player->setCurrentFieldIndex(playerPosition);

	playerPosition = player->getCurrentFieldIndex();

	Field* field= board->getFieldByIndex(playerPosition);

	std::cout << "You landed on field: "<< field->getName()<<" ("<< field->getIndex()<<")"<<std::endl;

	FieldType fieldType = field->getType();

	if (fieldType == FieldType::Property)
	{
		landOnProperty(board, bank, player, field);
	}
	else if (fieldType == FieldType::GoToJailField)
	{
		goToJail(board, bank, player);
	}
	else if (fieldType == FieldType::CardField)
	{
		std::cout << "Draw card";
	}

	if (dice[0] == dice[1])
	{
		std::cout << "You rolled a pair you get another roll!"<< std::endl;

		rollDice(board, bank, player, numberOfRolls + 1);
	}

	if (numberOfRolls != 1)
	{
		return;
	}

	int playerIndex = board->getActivePlayerIndex();
	playerIndex++;
	board->setActivePlayerIndex(playerIndex);
}

void MoveForwardCommand::goToJail(Board* board, Bank* bank, Player* player) const
{
	//to do
}

void MoveForwardCommand::landOnProperty(Board* board, Bank* bank, Player* player, Field* field) const
{
	PropertyField* propertyField = static_cast<PropertyField*>(field);

	MyString input = "";

	if (propertyField->getOwner() == nullptr)
	{
		if (player->getBalance() < propertyField->getPrice())
		{
			std::cout << "Not enough money to buy property"<<std::endl;
			std::cout << "Type anything to continue"<<std::endl;

			std::cin >> input;
			
			return;
		}

		std::cout << "Do you wanna buy property for " << propertyField->getPrice() <<"$? " << std::endl;
		std::cout << "y - yes buy property" << std::endl;
		std::cout << "n - dont buy property" << std::endl;

		std::cin >> input;

		if (input == "y")
		{
			bank->BuyProperty(propertyField, player);

			std::cout << "Property bought successfuly for " << propertyField->getPrice() << "$" << std::endl;
			std::cout << "New balance: " << player->getBalance() <<"$"<< std::endl;
			std::cout << "Type anything to continue" << std::endl;

			std::cin >> input;

			return;
		}
		else
		{
			return;
		}
	}


}