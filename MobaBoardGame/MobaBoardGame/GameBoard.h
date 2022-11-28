#pragma once
#include <array>
#include "GameSquare.h"

class GameBoard
{
public:
	GameBoard();
	GameBoard(int width, int height);

	void draw(sf::RenderWindow &window);
	const GameSquare *getConstSquare(float x, float y) const;  // Returns gameSquare containing point x, y in global coord.
	void changeSquare(float x, float y, SquareType type);

private:
	GameSquare *getSquare(float x, float y);  // Returns gameSquare containing point x, y in global coord.

	const int width = 121;
	const int height = 51;
	std::vector<std::vector<GameSquare>> board;
};

