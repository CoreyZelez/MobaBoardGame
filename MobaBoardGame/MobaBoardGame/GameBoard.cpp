#include "GameBoard.h"
#include "ImpassableSquare.h"
#include "PassableSquare.h"
#include "ActiveEntity.h"
#include <set>
#include <list>
#include <cstdlib>
#include <assert.h>
#include <iostream>

GameBoard::GameBoard()
{
	for(int x = 0; x < width; ++x)
	{
		std::vector<GameSquare> squareRow;
		for(int y = 0; y < height; ++y)
		{
			sf::Color fillColor(100, 150, 125);
			sf::Color outlineColor(100, 100, 150);
			squareRow.push_back(PassableSquare({ x, y }, grass));
		}
		board.push_back(squareRow);
	}

	changeSquare({ 21, 18 }, mountain);
	changeSquare({ 20, 17 }, mountain);
	changeSquare({ 20, 19 }, mountain);
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
			squareRow.push_back(ImpassableSquare({ col, row }, impassableForest));
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
	switch(type)
	{
	case impassableForest:
		*square = ImpassableSquare(square->getPosition(), impassableForest);
		break;
	case deepWater:
		*square = ImpassableSquare(square->getPosition(), deepWater);
		break;
	case mountain:
		*square = ImpassableSquare(square->getPosition(), mountain);
		break;
	case lava:
		*square = ImpassableSquare(square->getPosition(), lava);
		break;
	case grass:
		*square = PassableSquare(square->getPosition(), grass);
		break;
	case mountainFloor:
		*square = PassableSquare(square->getPosition(), mountainFloor);
		break;
	}
}

void GameBoard::changeSquare(Position position, SquareType type)
{
	GameSquare *square = &board[position.x][position.y];
	assert(square != nullptr);
	switch(type)
	{
	case impassableForest:
		*square = ImpassableSquare(square->getPosition(), impassableForest);
		break;
	case deepWater:
		*square = ImpassableSquare(square->getPosition(), deepWater);
		break;
	case mountain:
		*square = ImpassableSquare(square->getPosition(), mountain);
		break;
	case lava:
		*square = ImpassableSquare(square->getPosition(), lava);
		break;
	case grass:
		*square = PassableSquare(square->getPosition(), grass);
		break;
	case mountainFloor:
		*square = PassableSquare(square->getPosition(), mountainFloor);
		break;
	}
}

void GameBoard::markSquares(Position source, const int specialRange)
{
	const sf::Color color = sf::Color::Yellow;
	resetMarkedSquares();
	markedPositions = getInSpecialRangePositions(source, specialRange);
	for(Position position : markedPositions)
	{
		board[position.x][position.y].mark(color);
	}
}

void GameBoard::resetMarkedSquares()
{
	for(Position position : markedPositions)
	{
		board[position.x][position.y].unmark();
	}

	markedPositions.clear();
}

// Typically specialNum is the floor of (max / 2).
std::vector<Position> GameBoard::getInSpecialRangePositions(Position source, const int max)
{
	const int specialNum = max / 2;  // Max number of "bonus moves" that can be made. 
	
	// Performs bfs adding positions with depths <= max. Positions must be traversable on board.
	const int minX = source.x - max;
	const int maxX = source.x + max;
	const int minY = source.y - max;
	const int maxY = source.y + max;
	
	std::list<Position> candidates;
	
	// Find positions in square around pos.
	for(int x = minX; x <= maxX; ++x)
	{
		if(x < 0)
		{
			continue;
		}
		else if(x >= width)
		{
			break;
		}
	
		for(int y = minY; y <= maxY; ++y )
		{
			if(y < 0)
			{
				continue;
			}
			else if(y >= height)
			{
				break;  // Replace with goto to loop exit.
			}
	
	
			// Adds position if applicable.
			if(board[x][y].isVacant())
			{
				candidates.push_back({ x, y });
			}
		}
	}
	
	struct Node
	{
		Position position;
		int depth = -1;
	};
	
	// BFS
	std::list<Position> traversed;
	std::list<Node> queue;  
	// Handle start position.
	traversed.push_back(source);  // For ensuring we don't traverse same node twice.
	queue.push_back({ source, 0 });
	
	std::list<Position>::iterator i;
	
	while(!queue.empty()) {
		Node currNode = queue.front();
		Position currPos = currNode.position;
		const int currDepth = currNode.depth;
		queue.pop_front();
	
		if(currDepth == max + specialNum)
		{
			break;
		}
	
		Position left =  { currPos.x - 1, currPos.y };
		Position right = { currPos.x + 1, currPos.y };
		Position up =    { currPos.x    , currPos.y - 1 };
		Position down =  { currPos.x    , currPos.y + 1 };
		Position next[4] = { left, right, up, down };
	
		for(auto pos : next)
		{
			// Case pos is not a candidate.
			if(std::find(candidates.begin(), candidates.end(), pos) == candidates.end())
			{
				continue;
			}
			// Case pos is already traversed.
			if(std::find(traversed.begin(), traversed.end(), pos) != traversed.end())
			{
				continue;
			}
	
			queue.push_back(Node({pos, currDepth + 1}));
			traversed.push_back(pos);
		}
	}
	
	std::vector<Position> validPositions;
	for(Position position : traversed)
	{
		const int xDist = std::abs(position.x - source.x);
		const int yDist = std::abs(position.y - source.y);
		const int totalDist = xDist + yDist;
		for(int i = 0; i <= specialNum; ++i)
		{
			int trueMax = max;

			if(xDist >= i && yDist > 0)
			{
				trueMax += i;
			}
			else if(xDist >= 0 && yDist > i)
			{
				trueMax += i;
			}
			if(totalDist <= trueMax)
			{
				validPositions.push_back(position);
				break;
			}
		}
	}
	return validPositions;
	
}

Position GameBoard::globalCoordsToPosition(float x, float y)
{
	return getSquare(x, y)->getPosition();
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

GameSquare * GameBoard::getSquare(Position position)
{
	return &board[position.x][position.y];
}

bool GameBoard::moveEntity(Position source, Position target)
{
	if(source == target)
	{
		return false;
	}

	GameSquare *sourceSquare = getSquare(source);
	GameSquare *targetSquare = getSquare(target);

	assert(!sourceSquare->isVacant());
	assert(targetSquare->isVacant());

	if(targetSquare->isVacant())
	{
		ActiveEntity *entity = sourceSquare->removeOccupant();
		targetSquare->setOccupant(entity);
		return true;
	}
}

void GameBoard::initEntity(ActiveEntity * entity)
{
	Position entityPosition = entity->getPosition();
	GameSquare *square = &board[entityPosition.x][entityPosition.y];
	assert(square->isVacant());
	square->setOccupant(entity); 

}
