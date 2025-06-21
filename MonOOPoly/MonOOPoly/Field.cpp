#include "Field.h"

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

PrintableField* Field::getPrintable() const
{
	PrintableField* printableField = new PrintableField();

	MyString firstLine = "";

	printableField->setLine(0, firstLine);

	MyString nameLine = this->name;

	printableField->setLine(1, nameLine);

	MyString indexLine = "0";

	indexLine = index;

	printableField->setLine(2, indexLine);

	return printableField;
}
