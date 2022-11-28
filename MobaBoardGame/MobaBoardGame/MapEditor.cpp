#include "MapEditor.h"

MapEditor::MapEditor(int width, int height)
	: board(width, height)
{
}

void MapEditor::draw(sf::RenderWindow & window)
{
	board.draw(window);
}

void MapEditor::changeSquare(float x, float y)
{
	const GameSquare *square = board.getConstSquare(x, y);
	if(square == nullptr || square->getType() == currentType)
	{
		return;
	}

	board.changeSquare(x, y, currentType);
}

void MapEditor::setCurrentType(SquareType type)
{
	currentType = type;
}
