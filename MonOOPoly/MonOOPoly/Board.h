#pragma once
#include "Field.h"
#include "PrintableField.h"

class Board {
private:
	int numberOfFields;

	Field** fields;

	void loadFieldsFromFile(const char* path);

	void printEmptyFieldLine();

	void printTopOrBottomOfBoard(PrintableField** printableFields, int index);

	void printSideOfBoard(PrintableField** printableFields, int index);
	
	int getCorrectIndex(int index);

public:

	Board(const char* loadFromFilePath);

	void print();

	~Board();
};