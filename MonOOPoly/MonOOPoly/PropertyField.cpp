#pragma once
#include <string>
#include "PropertyField.h"
#include "PrintableField.h"
#include "Field.h"
#include "FieldType.h"
#include "Config.h"

PropertyField::PropertyField(int index, const MyString& name,
	const MyString& color,
	int price, int defaultRent, int cottagePrice, int castlePrice) : Field(index, FieldType::Property, name )
{
	this->color = color;
	this->price = price;
	this->defaultRent = defaultRent;
	this->cottagePrice = cottagePrice;
	this->castlePrice = castlePrice;
}

PrintableField* PropertyField::getPrintable() const
{
	PrintableField* printableField = new PrintableField();

	MyString priceLine = "0";

	priceLine = this->price;
	priceLine += "$";

	printableField->setLine(0, priceLine);

	MyString nameLine = this->color + " " + this->name;

	printableField->setLine(1, nameLine);

	MyString indexLine = "0";

	indexLine = this->index;

	printableField->setLine(2, indexLine);

	return printableField;
}