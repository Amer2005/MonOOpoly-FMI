#include "Field.h"
#include "StartField.h"
#include "PrintableField.h"

StartField::StartField(int index) : Field(index, FieldType::Start, "Start")
{
	
}

PrintableField* StartField::getPrintable() const
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