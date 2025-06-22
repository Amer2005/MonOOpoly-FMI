#include "Player.h"
#include "Config.h"
#include "ConsoleColor.h"

Player::Player(int index, const MyString& name)
{
	this->index = index;

	this->name = name;

	this->balance = Config::StartingMoney;

	this->currentFieldIndex = 0;
}

int Player::getCurrentFieldIndex()
{
	return currentFieldIndex;
}

void Player::setCurrentFieldIndex(int value)
{
	if (value < 0)
	{
		value = 0;
	}

	int numberOfFields = 2 * (Config::BoardWidth + Config::BoardHeight) - 4;

	if (value >= numberOfFields)
	{
		value = value % numberOfFields;
	}

	this->currentFieldIndex = value;
}

MyString Player::getName() 
{
	return this->name;
}

int Player::getIndex()
{
	return this->index;
}

int Player::getBalance()
{
	return this->balance;
}

void Player::setBalance(int value)
{
	if (value < 0)
	{
		value = 0;
	}

	this->balance = value;
}

bool Player::getIsInJail()
{
	return this->isInJail;
}

void Player::printName()
{
	ConsoleColor::setConsoleColor(static_cast<ColorType>(this->index + 1));

	std::cout << this->name;

	ConsoleColor::setConsoleColor(ColorType::Default);
}

void Player::setIsInJail(bool value)
{
	this->isInJail = value;
}

bool Player::getIsResigned()
{
	return this->isResigned;
}

void Player::setIsResigned(bool value)
{
	this->isResigned = value;
}
