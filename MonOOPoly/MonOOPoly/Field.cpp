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