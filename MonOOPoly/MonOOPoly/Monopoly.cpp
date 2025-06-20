#include "Monopoly.h"
#include "Board.h"
#include "Config.h"

void Monopoly::run()
{
	Board* board = new Board(Config::SaveFilePath);

	board->print();
}