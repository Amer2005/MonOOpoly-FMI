#pragma once
#include "MyString.h"
class PrintableField {
private:
	MyString* lines;
	int numberOfLines;

public:
	PrintableField();

	void printLine(int lineNumber);

	void setLine(int lineNumber, const MyString& content);
};
