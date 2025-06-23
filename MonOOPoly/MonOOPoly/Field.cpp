#include "Field.h"
#include <fstream>

Field::Field(int index, FieldType type, const MyString& name)
{
	this->index = index;
	this->type = type;
	this->name = name;
}

MyString Field::getName() const
{
	return this->name;
}

int Field::getIndex() const
{
	return this->index;
}

FieldType Field::getType() const
{
	return this->type;
}

PrintableField* Field::getPrintable()
{
	PrintableField* printableField = new PrintableField();

	if (this->type == FieldType::Jail)
	{
		printableField->setColor(ColorType::JailColor);
	}
	else if (this->type == FieldType::GoToJail)
	{
		printableField->setColor(ColorType::GoToJailColor);
	}
	else if (this->type == FieldType::Card)
	{
		printableField->setColor(ColorType::DrawCardColor);
	}
	else if (this->type == FieldType::Parking)
	{
		printableField->setColor(ColorType::ParkingColor);
	}
	else if (this->type == FieldType::Start)
	{
		printableField->setColor(ColorType::StartColor);
	}

	MyString firstLine = "";

	printableField->setLine(0, firstLine);

	MyString nameLine = this->name;

	printableField->setLine(1, nameLine);

	MyString indexLine = "0";

	indexLine = index;

	indexLine = "(" + indexLine + ")";

	printableField->setLine(2, indexLine);

	return printableField;
}