#include "Minion.h"
#include <assert.h>

Minion::Minion(GameBoard & gameBoard, const std::vector<Position> path, Team team)
	: GameEntity(team), gameBoard(gameBoard), path(path)
{
}

void Minion::move()
{
	assert(getPosition() == path[positionNum]);
}
