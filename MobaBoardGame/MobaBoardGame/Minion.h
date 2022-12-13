#pragma once
#include "GameEntity.h"
#include <array>

class PassiveAbility;

class Minion : public GameEntity
{
public:
	Minion(std::list<Position> path, std::array<EntityAttributes, 6> baseAttributes);

	void move();  // Moves to next position in path.

private:
	EntityAttributes currAttributes;
	std::array<EntityAttributes, 6> baseAttributes;
	
	std::list<Position> path;
	int positionNum;  // Should have path[positionNum] = actual position.

	std::unique_ptr<PassiveAbility> passive;  // Grants bonus stats based on health.

};

