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
	return 2000;
	return this->defaultRent;
}

Player* PropertyField::getOwner() {
	return owner;
}

void PropertyField::setOwner(Player* newOwner) {
	owner = newOwner;
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

	return printableField;
}