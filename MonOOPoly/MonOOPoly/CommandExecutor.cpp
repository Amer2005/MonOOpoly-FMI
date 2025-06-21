#pragma once
#include "CommandExecutor.h"
#include "Command.h"
#include "StartNewGameCommand.h";
#include "MoveForwardCommand.h"
void CommandExecutor::executeCommand(const MyString& input)
{
	Command* command;

	if (input == "start")
	{
		command = new StartNewGameCommand();
	}
	else if (input == "roll")
	{
		command = new MoveForwardCommand();
	}
	else
	{
		throw std::runtime_error("Please enter a valid command");
	}


	command->run(board, bank);
}

CommandExecutor::CommandExecutor(Board* board, Bank* bank)
{
	this->board = board;
	this->bank = bank;
}