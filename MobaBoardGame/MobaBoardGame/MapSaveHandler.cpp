#include "MapSaveHandler.h"
#include "GameBoard.h"
#include <fstream>
#include <iostream>

void MapSaveHandler::writeBoard(std::string filename, const GameBoard &board)
{
	std::vector<std::vector<SquareType>> squaresTypes = board.getSquaresTypes();

	std::ofstream myFile;
	myFile.open(filename, std::ios::trunc | std::ios::out);
	if(myFile.is_open())
	{
		for(const auto &row : squaresTypes)
		{
			for(const SquareType &squareType : row)
			{
				myFile << squareType << " ";
			}

			myFile << "-1\n";  // -1 indicates end of line.
		}
	}
}

std::unique_ptr<GameBoard> MapSaveHandler::readBoardFile(std::string filename)
{
	std::vector<std::vector<SquareType>> squaresTypes;

	std::ifstream myfile(filename, std::ios_base::in);

	int type;

	std::vector<SquareType> row;
	while(myfile >> type)
	{
		if(type == -1)
		{
			squaresTypes.push_back(row);
			row.clear();
			continue;
		}

		row.push_back(SquareType(type));
	}

	return std::make_unique<GameBoard>(squaresTypes);
}
