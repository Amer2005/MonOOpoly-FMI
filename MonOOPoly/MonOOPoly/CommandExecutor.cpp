#pragma once
#include "CommandExecutor.h"
#include "Command.h"
#include "StartNewGameCommand.h";
#include "MoveForwardCommand.h"
#include "ResignCommand.h"
#include "TradeCommand.h"
#include "GetPlayersInfoCommand.h"

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
	else if (input == "resign")
	{
		command = new ResignCommand();
	}
	else if (input == "trade")
	{
		command = new TradeCommand();
	}
	else if (input == "players")
	{
		command = new GetPlayersInfoCommand();
	}
	else
	{
		throw std::runtime_error("Please enter a valid command");
	}


	command->run(board, bank);
	
	delete command;
}

CommandExecutor::CommandExecutor(Board* board, Bank* bank)
{
	this->board = board;
	this->bank = bank;
}