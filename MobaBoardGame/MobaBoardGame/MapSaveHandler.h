#pragma once
#include "SquareType.h"
#include <string>

class GameBoard;

class MapSaveHandler
{
public:
	void writeBoard(std::string filename, const GameBoard &board);
	std::unique_ptr<GameBoard> readBoardFile(std::string filename);
	
private:

};

