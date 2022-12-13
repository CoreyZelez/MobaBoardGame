#include "GameBoard.h"
#include "ImpassableSquare.h"
#include "PassableSquare.h"
#include "GameEntity.h"
#include <set>
#include <list>
#include <cstdlib>
#include <assert.h>
#include <iostream>

GameBoard::GameBoard()
	: blueTeamSpawn()
{
	for(int x = 0; x < width; ++x)
	{
		std::vector<GameSquare> squareRow;
		for(int y = 0; y < height; ++y)
		{
			squareRow.push_back(PassableSquare({ x, y }, grass));
		}
		board.push_back(squareRow);
	}
}

GameBoard::GameBoard(int width, int height)
	: width(width), height(height)
{
	for(int x = 0; x < width; ++x)
	{
		std::vector<GameSquare> squareRow;
		for(int y = 0; y < height; ++y)
		{
			squareRow.push_back(ImpassableSquare({ x, y }, impassableForest));
		}
		board.push_back(squareRow);
	}

	changeSquare({ width / 2, 0 }, lava);
	changeSquare({ width / 2, height - 1 }, lava);
}

GameBoard::GameBoard(std::vector<std::vector<SquareType>> squaresTypes)
	: GameBoard(squaresTypes.size(), squaresTypes[0].size())
{
	for(int x = 0; x < width; ++x)
	{
		std::vector<GameSquare> squareRow;
		for(int y = 0; y < height; ++y)
		{
			SquareType squareType = squaresTypes[x][y];

			changeSquare({ x, y }, squareType);
		}
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

void GameBoard::initBlueSpawn(Position position)
{
	blueTeamSpawn = position;
}

void GameBoard::initRedSpawn(Position position)
{
	redTeamSpawn = position;
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

void GameBoard::markSquares(Position source, const int specialRange, bool onlyVacant, bool enhanceOne, sf::Color color)
{
	resetMarkedSquares();
	markedNodes = getInSpecialRangePositions(source, specialRange, onlyVacant, enhanceOne);
	for(Node node : markedNodes)
	{
		Position position = node.position;
		if(onlyVacant)
		{
			board[position.x][position.y].mark(color);

		}
		else
		{
			board[position.x][position.y].mark(color);
		}
	}
}

void GameBoard::resetMarkedSquares()
{
	for(Node node : markedNodes)
	{
		Position position = node.position;
		board[position.x][position.y].unmark();
	}

	markedNodes.clear();
}

// Typically specialNum is the floor of (max / 2).
std::list<Node> GameBoard::getInSpecialRangePositions(Position source, const int max, bool onlyVacant, bool enhanceOne)
{
	int specialNum = (((double)max) / 2) - 0.5;  // Max number of "bonus moves" that can be made. 
	if(enhanceOne && max == 1)
	{
		specialNum = 1;
	}
	
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
			if(onlyVacant && board[x][y].isVacant())
			{
				candidates.push_back({ x, y });
			}
			else if(!onlyVacant)
			{
				candidates.push_back({ x, y });
			}
		}
	}

	
	// BFS
	std::list<Position> traversed;
	std::list<Node> traversedNodes;
	std::list<Node> queue;  
	// Handle start position.
	traversed.push_back(source);  // For ensuring we don't traverse same node twice.
	queue.push_back({ source, 0 });
	traversedNodes.push_back({ source, 0 });

	std::list<Position>::iterator i;
	
	while(!queue.empty()) {
		Node currNode = queue.front();
		Position currPos = currNode.position;
		const int currDepth = currNode.value;
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
			traversedNodes.push_back(Node({ pos, currDepth + 1 }));
		}
	}
	
	std::list<Node> validNodes;
	for(Node node : traversedNodes)
	{
		Position position = node.position;
		const int depth = node.value;
		const int xDist = std::abs(position.x - source.x);
		const int yDist = std::abs(position.y - source.y);
		const int totalDist = node.value;  // I.e the depth.
		for(int i = 0; i <= specialNum; ++i)
		{
			int trueMax = max;

			if(xDist >= i && yDist > 0)
			{
				trueMax += i;
			}
			else if(xDist > 0 && yDist >= i)
			{
				trueMax += i;
			}

			if(totalDist > max && totalDist <= trueMax)
			{
				node.value = max;  // Analogous to changing cost for entity to travel to position.
				validNodes.push_back(node);
				break;
			}
			else if(totalDist <= max)
			{
				validNodes.push_back(node);
				break;
			}
		}
	}
	return validNodes;
	
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

std::list<Node> GameBoard::getMarkedNodes()
{
	return markedNodes;
}

std::vector<std::vector<SquareType>> GameBoard::getSquaresTypes() const
{
	std::vector<std::vector<SquareType>> squaresTypes;

	for(const auto &boardRow : board)
	{
		std::vector<SquareType> squareTypesRow;

		for(const GameSquare &square : boardRow)
		{
			squareTypesRow.push_back(square.getType());
		}

		squaresTypes.push_back(squareTypesRow);
	}

	return squaresTypes;
}

Position GameBoard::getSpawn(Team team)
{
	switch(team)
	{
	case blue:

		// IN ACTUALITY SHOULD USE BFS TO FIND FIRST EMPTY SQUARE AROUND SPAWN AND RETURN THAT.
		return blueTeamSpawn;
		break;

	case red:
		return redTeamSpawn;
		break;
	}
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
		GameEntity *entity = sourceSquare->removeOccupant();
		targetSquare->setOccupant(entity);
		return true;
	}
}

void GameBoard::initEntity(GameEntity * entity)
{
	Position entityPosition = entity->getPosition();
	GameSquare *square = &board[entityPosition.x][entityPosition.y];
	assert(square->isVacant());
	square->setOccupant(entity); 

}
