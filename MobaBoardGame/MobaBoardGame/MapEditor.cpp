#include "MapEditor.h"

MapEditor::MapEditor(int width, int height)
	: board(std::make_unique<GameBoard>(width, height))
{

}

void MapEditor::draw(sf::RenderWindow & window)
{
	board.get()->draw(window);
}

void MapEditor::changeSquare(float x, float y)
{
	const GameSquare *square = board.get()->getConstSquare(x, y);
	if(square == nullptr || square->getType() == currentType)
	{
		return;
	}

	board.get()->changeSquare(x, y, currentType);
}

void MapEditor::setCurrentType(SquareType type)
{
	currentType = type;
}

void MapEditor::exportMap(std::string filename)
{
	mapSaveHandler.writeBoard(filename, *board.get());
}

void MapEditor::importMap(std::string filename)
{
	board = mapSaveHandler.readBoardFile(filename);
}
