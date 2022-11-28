#pragma once
#include <vector>
#include "GameBoard.h"
#include "SquareType.h"

class MapEditor
{
public:
	MapEditor(int width, int height);

	void draw(sf::RenderWindow &window);
	void changeSquare(float x, float y);
	void setCurrentType(SquareType type);

private:
	SquareType currentType = deepWater;
	GameBoard board;
};

