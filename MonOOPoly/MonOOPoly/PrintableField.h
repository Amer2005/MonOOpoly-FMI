#pragma once
#include "MyString.h"
#include "ColorType.h"
class PrintableField {
private:
	MyString* lines;
	int numberOfLines;
	
	ColorType color;

public:
	PrintableField();

	void setColor(ColorType color);

	void printLine(int lineNumber);

	void setLine(int lineNumber, const MyString& content);
};
