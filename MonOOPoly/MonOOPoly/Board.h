#pragma once
#include "Field.h"
#include "PrintableField.h"
#include "Player.h"

class CardDeck;
class CardModel;

class Board {
private:
	bool isGameOver = false;

	int numberOfFields;

	int playerCount;

	int activePlayerIndex = 0;

	Field** fields;

	Player** players;

	CardDeck* cardDeck;

	void loadFieldsFromFile(const char* path);

	void printEmptyFieldLine();

	void printTopOrBottomOfBoard(PrintableField** printableFields, int index);

	void printSideOfBoard(PrintableField** printableFields, int index);
	
	int getCorrectIndex(int index);

	void free();

public:

	Board(const char* loadFromFilePath);

	void print();

	bool getIsGameOver();

	int getActivePlayerIndex();

	void setActivePlayerIndex(int value);

	void setPlayers(MyString** names, int playerCount);

	Player* getPlayerByIndex(int index);

	Field* getFieldByIndex(int index);

	int getJailFieldIndex();

	void endTurn();

	int getNumberOfPropertiesOwnedByPlayer(int playerIndex);

	int getPlayerCount();

	int getFieldCount();

	bool doesPlayerOwnAllPropertiesOfColor(int playerIndex, MyString color);

	void saveToFile(const char* path);

	void loadFromFile(const char* path);

	CardModel* drawCard();

	~Board();
};