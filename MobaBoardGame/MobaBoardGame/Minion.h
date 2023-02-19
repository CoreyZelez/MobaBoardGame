#pragma once
#include "GameEntity.h"
#include "MinionAttributesSystem.h"
#include <array>

class PassiveAbility;
class Game;

class Minion : public GameEntity
{
public:
	Minion(Game &game, Team team, std::vector<Position> path, int level, std::vector<EntityAttributes> coreBaseAttributes);

	void initImageHealth();

	EntityAttributes& getAttributes();
	EntityAttributes getAttributes() const;
	EntityAttributes getBaseAttributes() const;

	int takeDamage(int damage);  // Returns true damage dealt.

	void update();
	void merge(Minion &minion);  // Merges current health of minion to this minion.

	void handleDeath();

	void move();  // Moves to next position in path.

	//void attackTower();
	void attackMinion();
	void attackCharacter();

private:
	int bonusPhysicalDamage() const;

	std::vector<Minion*> getAdjacentMinions() const;
	std::vector<Character*> getAdjacentCharacters() const;

	Position firstVacantPathPosition();

	MinionAttributesSystem attributesSystem;

	const std::vector<Position> path;
	int positionNum;  // Should have path[positionNum] = actual position.

	std::unique_ptr<PassiveAbility> passive;  // Grants bonus stats based on health.

	Game &game;
	GameBoard &gameBoard;
};

