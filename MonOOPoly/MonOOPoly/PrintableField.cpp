#include "PrintableField.h"
#include "Config.h"
#include "MyString.h"
#include "ConsoleUtil.h"

PrintableField::PrintableField()
{
	this->numberOfLines = Config::FieldHeight;

	this->lines = new MyString[Config::FieldHeight]();

	this->color = ColorType::Default;
}

void PrintableField::setColor(ColorType color)
{
	this->color = color;
}

void PrintableField::printLine(int lineNumber)
{
	int maxLength = Config::FieldWidth;

	ConsoleUtil::setConsoleColor(this->color);

	if (lineNumber == -1)
	{
		std::cout << "+";

		for (int i = 0; i < maxLength; i++)
		{
			std::cout << "-";
		}

		std::cout << "+";

		ConsoleUtil::setConsoleColor(ColorType::Default);

		return;
	}

	if (lineNumber < 0 || lineNumber >= numberOfLines)
	{
		for (int i = 0; i < maxLength; i++)
		{
			std::cout << " ";
		}

		ConsoleUtil::setConsoleColor(ColorType::Default);

		return;
	}



	MyString printedLine = lines[lineNumber];

	int length = printedLine.length();

	if (length < maxLength)
	{
		MyString tempString = "";

		int numberOfEmpty = maxLength - length;

		for (int i = 0; i < numberOfEmpty / 2; i++)
		{
			tempString += " ";
		}

		tempString += printedLine;

		for (int i = 0; i < numberOfEmpty / 2 + numberOfEmpty % 2; i++)
		{
			tempString += " ";
		}

		printedLine = tempString;
	}
	else if (length > maxLength)
	{
		MyString tempString = "";
		
		length = maxLength;

		for (int i = 0;i < maxLength;i++)
		{
			char* curr = new char[2];
			curr[0] = printedLine[i];
			curr[1] = '\0';
			tempString += curr;
		}

		printedLine = tempString;
	}

	printedLine = "|" + printedLine + "|";

	std::cout << printedLine;

	ConsoleUtil::setConsoleColor(ColorType::Default);
}

void PrintableField::setLine(int lineNumber, const MyString& content)
{
	if (lineNumber < 0 || lineNumber >= numberOfLines)
	{
		return;
	}

	this->lines[lineNumber] = content;
}