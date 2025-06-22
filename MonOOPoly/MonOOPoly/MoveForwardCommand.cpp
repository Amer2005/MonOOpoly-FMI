#include "MoveForwardCommand.h"
#include "Dice.h"
#include "PropertyField.h"
#include <iostream>

void MoveForwardCommand::run(Board* board, Bank* bank) const
{
	int activePlayerIndex = board->getActivePlayerIndex();
	Player* player = board->getPlayerByIndex(activePlayerIndex);

	this->rollDice(board, bank, player, 1);
}

void MoveForwardCommand::waitForAnyInput() const
{
	system("pause");
	//std::cout << "Type anything to continue" << std::endl;
	//MyString input = "";
	//std::cin >> input;
}

void MoveForwardCommand::rollDice(Board* board, Bank* bank, Player* player, int numberOfRolls) const
{
	int* dice = new int[2];

	dice[0] = Dice::rollDice();
	dice[1] = Dice::rollDice();

	std::cout << "Dice rolls: " << dice[0] << " " << dice[1] << std::endl;

	if (player->getIsInJail())
	{
		if (dice[0] == dice[1])
		{
			std::cout << "You get out of jail" << std::endl;

			player->setIsInJail(false);

			waitForAnyInput();

			rollDice(board, bank, player, numberOfRolls + 1);
		}
		else
		{
			std::cout << "You stay in jail" << std::endl;

			waitForAnyInput();

			if(numberOfRolls == 1)
				board->endTurn();
		}

		return;
	}

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
	else if (fieldType == FieldType::GoToJail)
	{
		std::cout << "You landed on go to jail field!" << std::endl;

		goToJail(board, bank, player);
	}
	else if (fieldType == FieldType::Card)
	{
		std::cout << "Draw card!" << std::endl;

		waitForAnyInput();
	}
	else
	{
		std::cout << "You landed on: " << field->getName() << "(" << field->getIndex() << ")" <<std::endl;
		
		waitForAnyInput();
	}

	if (dice[0] == dice[1] && !board->getIsGameOver())
	{
		std::cout << "You rolled a pair you get another roll!"<< std::endl;

		rollDice(board, bank, player, numberOfRolls + 1);
	}

	if (numberOfRolls != 1)
	{
		return;
	}

	board->endTurn();

	return;
}

void MoveForwardCommand::goToJail(Board* board, Bank* bank, Player* player) const
{
	MyString input = "";

	int* dice = new int[2];

	dice[0] = Dice::rollDice();
	dice[1] = Dice::rollDice();

	player->setIsInJail(true);

	int jailFieldIndex = board->getJailFieldIndex();

	player->setCurrentFieldIndex(jailFieldIndex);

	std::cout << "You rolled " << dice[0] << " " << dice[1] << std::endl;
	if (dice[0] == dice[1])
	{
		std::cout << "Its a pair! You get out free." << std::endl;
		player->setIsInJail(false);
	}
	else
	{
		std::cout << "Not a pair you stay in jail at field: ";
		std::cout << jailFieldIndex << std::endl;
	}

	waitForAnyInput();
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
			
			waitForAnyInput();
			
			return;
		}

		std::cout << "Do you wanna buy property for " << propertyField->getPrice() <<"$? " << std::endl;
		std::cout << "y - yes buy property" << std::endl;
		std::cout << "n - dont buy property" << std::endl;

		std::cin >> input;

		if (input == "y")
		{
			bank->buyProperty(propertyField, player);

			std::cout << "Property bought successfuly for " << propertyField->getPrice() << "$" << std::endl;
			std::cout << "New balance: " << player->getBalance() <<"$"<< std::endl;
			
			waitForAnyInput();

			return;
		}
		else
		{
			return;
		}
	}
	else
	{
		Player* owner = propertyField->getOwner();

		if (owner->getIndex() == player->getIndex())
		{
			std::cout << "You landed on your own property " << propertyField->getName()
				<< "(" << propertyField->getIndex() << ")" << std::endl;
		}
		else {
			std::cout << "You have to pay "<< propertyField->getCurrentRent() <<"$ rent to ";
			owner->printName();
			std::cout<<std::endl;

			bank->payRent(board, propertyField, player);
		}

		waitForAnyInput();
	}

}