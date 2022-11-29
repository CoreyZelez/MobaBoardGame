#pragma once
#include <array>
#include "GameSquare.h"




class GameBoard
{
public:
	GameBoard();
	GameBoard(int width, int height);

	void draw(sf::RenderWindow &window);

	// Getters
	const GameSquare *getConstSquare(float x, float y) const;  // Returns gameSquare containing global coord x,y.
	GameSquare *getSquare(float x, float y);  // Returns gameSquare containing point x, y in global coord.
	GameSquare *getSquare(Position position);  // Returns gameSquare with given position.

	// Entities
	bool moveEntity(Position source, Position target);  // True indicates success.
	void initEntity(ActiveEntity *entity);

	// Squares
	void changeSquare(float x, float y, SquareType type);
	void changeSquare(Position position, SquareType type);
	void markSquares(Position source, const int specialRange);  // Uses getInSpecialRangePositions.
	void resetMarkedSquares();

	// Utility
	std::vector<Position> getInSpecialRangePositions(Position source, const int max);  // Maybe should be private.
	Position globalCoordsToPosition(float x, float y);

private:
	const int width = 121;
	const int height = 51;
	std::vector<std::vector<GameSquare>> board;  // Use pointers to GameSquare !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	std::vector<Position> markedPositions;  // Positions that are marked to indicate character may move to.
};

