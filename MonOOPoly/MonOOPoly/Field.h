#pragma once
#include "MyString.h"
#include "FieldType.h"
#include "PrintableField.h"

class Field {
protected:
	int index;

	FieldType type;

	MyString name;

	Field(int index, FieldType type, const MyString& name);
	
public:
	MyString getName() const;

	int getIndex() const;

	FieldType getType() const;

	virtual PrintableField* getPrintable() const;
};