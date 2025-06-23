#pragma once
#include <string>
#include "PropertyField.h"
#include "PrintableField.h"
#include "Field.h"
#include "FieldType.h"
#include "Config.h"

int PropertyField::getPrice() {
	return price;
}

int PropertyField::getDefaultRent() {
	return defaultRent;
}

int PropertyField::getCottagePrice() {
	return cottagePrice;
}

int PropertyField::getCastlePrice() {
	return castlePrice;
}

int PropertyField::getCurrentRent()
{
	double rent = this->defaultRent;

	for (int i = 0; i < numberOfCottages; i++)
	{
		rent = rent * (Config::CottagePriceIncreasePercentage + 100) / 100;
	}

	for (int i = 0; i < numberOfCastles; i++)
	{
		rent = rent * (Config::CastlePriceIncreasePercentage + 100) / 100;
	}

	return rent;
}

Player* PropertyField::getOwner() {
	return owner;
}

void PropertyField::setOwner(Player* newOwner) {
	owner = newOwner;
}

int PropertyField::getNumberOfCottages()
{
	return this->numberOfCottages;
}

void PropertyField::setNumberOfCottages(int value)
{
	if (value < 0 || value > Config::MaxNumberOfCottages)
	{
		return;
	}

	this->numberOfCottages = value;
}

int PropertyField::getNumberOfCastles()
{
	return this->numberOfCastles;
}

void PropertyField::setNumberOfCastles(int value)
{
	if (value < 0 || value > Config::MaxNumberOfCastles)
	{
		return;
	}

	this->numberOfCastles = value;
}

MyString PropertyField::getColor()
{
	return this->color;
}

PropertyField::PropertyField(int index, const MyString& name,
	const MyString& color,
	int price, int defaultRent, int cottagePrice, int castlePrice) : Field(index, FieldType::Property, name)
{
	this->color = color;
	this->price = price;
	this->defaultRent = defaultRent;
	this->cottagePrice = cottagePrice;
	this->castlePrice = castlePrice;
	this->numberOfCottages = 0;
	this->numberOfCastles = 0;
}

PrintableField* PropertyField::getPrintable()
{
	PrintableField* printableField = new PrintableField();

	if (this->owner != nullptr)
	{
		int playerIndex = this->owner->getIndex();

		ColorType color = static_cast<ColorType>(playerIndex + 1);

		printableField->setColor(color);
	}

	MyString priceLine = "";
	MyString priceString = "";
	MyString rentString = "";

	priceString = this->price;
	rentString = this->getCurrentRent();
	priceLine += (priceString + "$ " + rentString + "$");

	printableField->setLine(0, priceLine);

	MyString nameLine = this->color + " " + this->name;

	printableField->setLine(1, nameLine);

	MyString indexLine = "0";

	indexLine = this->index;

	indexLine = "(" + indexLine + ")";

	printableField->setLine(2, indexLine);

	MyString buildingsLine = "";

	for (int i = 0;i < this->getNumberOfCottages();i++)
	{
		buildingsLine += "^";

		if (i != this->getNumberOfCottages() + this->getNumberOfCastles() - 1)
		{
			buildingsLine += " ";
		}
	}

	for (int i = 0;i < this->getNumberOfCastles();i++)
	{
		buildingsLine += "#";

		if (this->getNumberOfCottages() + i != this->getNumberOfCottages() + this->getNumberOfCastles() - 1)
		{
			buildingsLine += " ";
		}
	}

	printableField->setLine(3, buildingsLine);

	return printableField;
}