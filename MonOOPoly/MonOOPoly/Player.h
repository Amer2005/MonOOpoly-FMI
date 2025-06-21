#pragma once
#include "MyString.h"

class Player {
private:
	int index = 0;

	bool isResigned = false;

	int currentFieldIndex = 0;

	int balance = 0;

	MyString name;
public:

	Player(int index,const MyString& name);

	int getCurrentFieldIndex();

	void setCurrentFieldIndex(int value);

	MyString getName();

	int getIndex();
	
	int getBalance();

	void setBalance(int value);

};