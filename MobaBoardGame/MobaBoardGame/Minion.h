#pragma once
#include "GameEntity.h"
#include "MinionAttributesSystem.h"
#include <array>

class PassiveAbility;

class Minion : public GameEntity
{
public:
	Minion(GameBoard &gameBoard, const std::vector<Position> path, Team team);

	void move();  // Moves to next position in path.

private:
	MinionAttributesSystem attributesSystem;

	const std::vector<Position> path;
	int positionNum;  // Should have path[positionNum] = actual position.

	std::unique_ptr<PassiveAbility> passive;  // Grants bonus stats based on health.

	GameBoard &gameBoard;

};

