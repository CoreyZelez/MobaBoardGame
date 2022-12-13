#pragma once
#include <vector>
#include "GameBoard.h"
#include "SquareType.h"
#include "MapSaveHandler.h"

class MapEditor
{
public:
	MapEditor(int width, int height);
	MapEditor(std::string filename);

	void draw(sf::RenderWindow &window);
	void changeSquare(float x, float y);
	void setCurrentType(SquareType type);

	void exportMap(std::string filename);
	void importMap(std::string filename);

private:
	SquareType currentType = deepWater;

	std::unique_ptr<GameBoard> board;
	MapSaveHandler mapSaveHandler;
};

