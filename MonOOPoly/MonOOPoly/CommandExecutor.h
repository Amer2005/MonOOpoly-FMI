#pragma once
#include "Board.h"
#include "Bank.h"
#include "UpgradePropertyCommand.h"
class CommandExecutor
{
private:
	Board* board;
	Bank* bank;

public:
	CommandExecutor(Board* board, Bank* bank);

	void executeCommand(const MyString& command);
};