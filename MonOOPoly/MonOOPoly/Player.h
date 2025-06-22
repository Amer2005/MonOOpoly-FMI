#pragma once
#include "MyString.h"

class Player {
private:
	int index = 0;

	bool isResigned = false;

	int currentFieldIndex = 0;

	int balance = 0;

	bool isInJail = false;

	MyString name;
public:

	Player(int index,const MyString& name);

	int getCurrentFieldIndex();

	void setCurrentFieldIndex(int value);

	MyString getName();

	int getIndex();
	
	int getBalance();

	void setBalance(int value);

	bool getIsInJail();

	void printName();

	void setIsInJail(bool value);

	bool getIsResigned();

	void setIsResigned(bool value);
};