#pragma once
#include <list>
#include "GameSquare.h"
#include "Team.h"


struct Node
{
	Position position;
	int value = -1;

	inline Node operator=(const Node& b) {
		Node node;
		node.position = b.position;
		node.value = b.value;
		return node;
	}
};


class GameBoard
{
public:
	GameBoard();
	GameBoard(int width, int height);
	GameBoard(std::vector<std::vector<SquareType>> squaresTypes);

	void draw(sf::RenderWindow &window);

	void initBlueSpawn(Position position);
	void initRedSpawn(Position position);

	// Getters
	const GameSquare *getConstSquare(float x, float y) const;  // Returns gameSquare containing global coord x,y.
	GameSquare *getSquare(float x, float y);  // Returns gameSquare containing point x, y in global coord.
	GameSquare *getSquare(Position position);  // Returns gameSquare with given position.
	std::list<Node> getMarkedNodes();
	std::vector<std::vector<SquareType>> getSquaresTypes() const;
	Position getSpawn(Team team);

	// Entities
	bool moveEntity(Position source, Position target);  // True indicates success.
	void initEntity(GameEntity *entity);

	// Squares
	void changeSquare(float x, float y, SquareType type);
	void changeSquare(Position position, SquareType type);
	void markSquares(Position source, const int specialRange, bool onlyVacant, bool enhanceOne, sf::Color color);  // Uses getInSpecialRangePositions. 
	void resetMarkedSquares();

	// Utility
	std::list<Node> getInSpecialRangePositions(Position source, const int max, bool onlyVacant, bool enhanceOne);  // enhanceOne includes diagonals on max = 1.
	Position globalCoordsToPosition(float x, float y);

private:
	Position blueTeamSpawn;
	Position redTeamSpawn;
	const int width = 121;
	const int height = 51;
	std::vector<std::vector<GameSquare>> board;  // Use pointers to GameSquare !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	std::list<Node> markedNodes;  // Nodes i.e. positions that are marked to indicate character may move to.
};

