#include "GameBoard.h"
#include "ImpassableBoardSquare.h"
#include <assert.h>
#include <iostream>

GameBoard::GameBoard()
{
	for(int row = 0; row < height; ++row)
	{
		std::vector<GameSquare> squareRow;
		for(int col = 0; col < width; ++col)
		{
			sf::Color fillColor(100, 150, 125);
			sf::Color outlineColor(100, 100, 150);
			squareRow.push_back(ImpassableBoardSquare({ col, row }, impassableForest));
		}
		board.push_back(squareRow);
	}
}

GameBoard::GameBoard(int width, int height)
	: width(width), height(height)
{
	for(int row = 0; row < height; ++row)
	{
		std::vector<GameSquare> squareRow;
		for(int col = 0; col < width; ++col)
		{
			sf::Color fillColor(100, 150, 125);
			sf::Color outlineColor(100, 100, 150);
			squareRow.push_back(ImpassableBoardSquare({ col, row }, impassableForest));
		}
		board.push_back(squareRow);
	}
}

void GameBoard::draw(sf::RenderWindow & window)
{
	for(const auto &row : board)
	{
		for(const auto &gameSquare : row)
		{
			gameSquare.draw(window);
		}
	}
}

const GameSquare * GameBoard::getConstSquare(float x, float y) const
{
	for(const std::vector<GameSquare> &row : board)
	{
		for(const GameSquare &gameSquare : row)
		{
			if(gameSquare.getRect().getGlobalBounds().contains(x, y))
			{
				return &gameSquare;
			}
		}
	}

	return nullptr;
}

void GameBoard::changeSquare(float x, float y, SquareType type)
{
	GameSquare *square = getSquare(x, y);
	assert(square != nullptr);
	std::cout << 4378743843 << std::endl;
	switch(type)
	{
	case impassableForest:
		*square = ImpassableBoardSquare(square->getPosition(), impassableForest);
	case deepWater:
		*square = ImpassableBoardSquare(square->getPosition(), deepWater);
	}
}

GameSquare * GameBoard::getSquare(float x, float y)
{
	for(std::vector<GameSquare> &row : board)
	{
		for(GameSquare &square : row)
		{
			if(square.getRect().getGlobalBounds().contains(x, y))
			{
				return &square;
			}
		}
	}

	return nullptr;
}
