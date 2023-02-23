#include "Minion.h"
#include "Character.h"
#include "Game.h"
#include <assert.h>
#include <cstdlib>

const double PHYSICAL_DAMAGE_RATIO = 0.015;  // as percent of health.

Minion::Minion(Game &game, Team team, std::vector<Position> path, int level, std::vector<EntityAttributes> coreBaseAttributes)
	: GameEntity(team, ActiveEntityImage(team, true)), game(game), gameBoard(game.getBoard()), 
	path(path), attributesSystem(*this, level, coreBaseAttributes)
{
	// Determines initial spawn position (First vacant position in path on board).
	Position spawnPosition = { -1, -1 };
	for(int n = 0; n < path.size(); ++n)
	{
		GameSquare &square = *gameBoard.getSquare(path[n]);
		if(square.isVacant())
		{
			positionNum = n;
			spawnPosition = path[n];
			break;
		}
	}

	assert(spawnPosition.x != -1 && spawnPosition.y != -1 );  // I.E. should find vacant path position above.

	GameEntity::move(spawnPosition);

	// Updates position on gameBoard.
	GameSquare &targetSquare = *gameBoard.getSquare(spawnPosition);
	assert(targetSquare.isVacant());
	targetSquare.setOccupant(this);
}

void Minion::initImageHealth()
{
	const EntityAttributes &currAttributes = attributesSystem.getAttributes();
	const EntityAttributes &baseAttributes = attributesSystem.getBaseAttributes();
	setHealth(currAttributes.healthAttributes.health, baseAttributes.healthAttributes.health);  // MUST BE RECALLED WHEN LEVELING UP!!!
}

EntityAttributes& Minion::getAttributes()
{
	return attributesSystem.getAttributes();
}

EntityAttributes Minion::getAttributes() const
{
	return attributesSystem.getAttributes();
}

EntityAttributes Minion::getBaseAttributes() const
{
	return attributesSystem.getBaseAttributes();
}

int Minion::takeDamage(int damage)
{
	int &health = attributesSystem.getAttributes().healthAttributes.health;
	if(damage > health)
	{
		damage = health;
	}

	health -= damage;

	handleDeath();

	return damage;
}


int Minion::bonusPhysicalDamage() const
{
	const int health = attributesSystem.getAttributes().healthAttributes.health;
	return (double)health * PHYSICAL_DAMAGE_RATIO;
}

std::vector<Minion*> Minion::getAdjacentMinions() const
{
	std::vector<Minion *> adjacent;
	std::vector<Position> positions;

	for(int i = -1; i <= 1; ++i)
	{
		for(int j = -1; j <= 1; ++j)
		{
			if(i == 0 && j == 0)
			{
				continue;
			}
			Position pos = getPosition();
			pos.x += i;
			pos.y += j;
			positions.push_back(pos);
		}
	}

	for(Position pos : positions)
	{
		adjacent.push_back(game.getMinionAt(pos));
	}

	return adjacent;
}

std::vector<Character*> Minion::getAdjacentCharacters() const
{
	std::vector<Character *> adjacent;

	// Adjacent positions.
	Position pos1 = getPosition();
	pos1.x += 1;
	Position pos2 = getPosition();
	pos2.x -= 1;
	Position pos3 = getPosition();
	pos3.y += 1;
	Position pos4 = getPosition();
	pos4.y -= 1;
	Position pos5 = getPosition();
	pos5.x += 1;
	pos5.y += 1;
	Position pos6 = getPosition();
	pos6.x += 1;
	pos6.y -= 1;
	Position pos7 = getPosition();
	pos7.x -= 1;
	pos7.y += 1;
	Position pos8 = getPosition();
	pos8.x -= 1;
	pos8.y -= 1;

	// Possible adjacent minions.
	adjacent.push_back(game.getCharacterAt(pos1));
	adjacent.push_back(game.getCharacterAt(pos2));
	adjacent.push_back(game.getCharacterAt(pos3));
	adjacent.push_back(game.getCharacterAt(pos4));
	adjacent.push_back(game.getCharacterAt(pos5));
	adjacent.push_back(game.getCharacterAt(pos6));
	adjacent.push_back(game.getCharacterAt(pos7));
	adjacent.push_back(game.getCharacterAt(pos8));

	return adjacent;
}



void Minion::update()
{
	std::cout << "second " << this << std::endl;

	attributesSystem.update();

	std::cout << "third " << this << std::endl;
	// attackTower();
	move();
	attackMinion();
	attackCharacter();
}

void Minion::merge(Minion &minion)
{
	EntityAttributes &currAttributes = attributesSystem.getAttributes();
	EntityAttributes &mergeeCurrAttributes = minion.attributesSystem.getAttributes();
	currAttributes.healthAttributes.health += mergeeCurrAttributes.healthAttributes.health;
	game.remove(minion);
}

void Minion::handleDeath()
{
	// Handles death.
	if(!attributesSystem.isAlive())
	{
		game.remove(*this);
	}
}

void Minion::move()
{
	assert(getPosition() == path[positionNum]);

	const int fixedActionCost = 1;  // Note: minions can do precisely 1 action per turn.

	const int nextPositionNum = positionNum + 1;
	Position currPosition = getPosition();
	Position targetPosition = path[nextPositionNum];

	GameSquare &sourceSquare = *gameBoard.getSquare(currPosition);
	GameSquare &targetSquare = *gameBoard.getSquare(targetPosition);

	EntityAttributes& currAttributes = attributesSystem.getAttributes();

	// Case minion cannot move.
	if(!(currAttributes.actionAttributes.points == fixedActionCost
		&& currAttributes.actionAttributes.movementPoints == fixedActionCost))
	{
		return;
	}

	// Handles movement of minion.
	if(targetSquare.isVacant())
	{
		targetSquare.setOccupant(this);
		GameEntity::move(targetPosition);

		currAttributes.actionAttributes.points -= fixedActionCost;
		currAttributes.actionAttributes.movementPoints -= fixedActionCost;

		positionNum = nextPositionNum;
		sourceSquare.removeOccupant();
	}
	else if(targetSquare.getOccupant() == nullptr)  // Target square immovable.
	{
		// No movement.
	}
	else if(targetSquare.getOccupant()->getTeam() == getTeam())  
	{
		Minion *minion = game.getMinionAt(targetSquare.getPosition());
		Character *character = game.getCharacterAt(targetSquare.getPosition());

		assert(minion == nullptr || character == nullptr); 

		if(minion != nullptr)  // Merge minions.
		{
			merge(*minion);

			// Moves minion to position of mergee.
			targetSquare.setOccupant(this);
			GameEntity::move(targetPosition);

			currAttributes.actionAttributes.points -= fixedActionCost;
			currAttributes.actionAttributes.movementPoints -= fixedActionCost;

			positionNum = nextPositionNum;
			sourceSquare.removeOccupant();
		}
		else if(character != nullptr)  // Swap minion positions with character position (same team).
		{
			gameBoard.swapPositions(this, character);
			currAttributes.actionAttributes.points -= fixedActionCost;
			currAttributes.actionAttributes.movementPoints -= fixedActionCost;
			positionNum = nextPositionNum;
		}
	}
}

void Minion::attackMinion()
{
	if(!attributesSystem.canAttack())
	{
		return;
	}

	// Adjacent positions.
	std::vector<Minion*> adjacent = getAdjacentMinions();

	// Creates vector of non nullptr minions of opposing team from above.
	std::vector<Minion*> minions;

	for(Minion *minion : adjacent)
	{
		if(minion != nullptr && minion->getTeam() != getTeam())
		{
			minions.push_back(minion);
		}
	}

	// No adjacent minions.
	if(minions.size() == 0)
	{
		return;
	}

	const int size = minions.size();
	const int chosen = std::rand() % size;
	Minion &minion = *minions[chosen];


	// Handling the attack.
	EntityAttributes &currAttributes = attributesSystem.getAttributes();

	int &attackPoints = currAttributes.actionAttributes.attackPoints;
	int &points = currAttributes.actionAttributes.points;
	const int attackCost = currAttributes.actionAttributes.attackCost;
	const int range = currAttributes.actionAttributes.range;

	// Update action points.
	attackPoints -= attackCost;
	points -= attackCost;

	// Calculate damage.
	const double mult = calculatePhysicalDamageMultiplier(minion.getAttributes().combatAttributes.armor,
		currAttributes.combatAttributes.armorPenetration,
		currAttributes.combatAttributes.lethality);
	const int physicalDamage = currAttributes.combatAttributes.physicalDamage + bonusPhysicalDamage();
	const int damage = mult * (double)physicalDamage;

	// Deal damage.
	if(damage >= 0)
	{
		minion.takeDamage(damage);
	}
}

void Minion::attackCharacter()
{
	if(!attributesSystem.canAttack())
	{
		return;
	}

	std::vector<Character*> adjacentCharacters = getAdjacentCharacters();

	// Creates vector of non nullptr characters of opposing team from above.
	std::vector<Character*> characters;

	for(Character *character : adjacentCharacters)
	{
		if(character != nullptr && character->getTeam() != getTeam())
		{
			characters.push_back(character);
		}
	}

	// No adjacent characters.
	if(characters.size() == 0)
	{
		return;
	}

	const int size = characters.size();
	const int chosen = std::rand() % size;
	Character &character = *characters[chosen];


	// Handling the attack.
	EntityAttributes &currAttributes = attributesSystem.getAttributes();

	int &attackPoints = currAttributes.actionAttributes.attackPoints;
	int &points = currAttributes.actionAttributes.points;
	const int attackCost = currAttributes.actionAttributes.attackCost;
	const int range = currAttributes.actionAttributes.range;

	// Update action points.
	attackPoints -= attackCost;
	points -= attackCost;

	// Calculate damage.
	const double mult = calculatePhysicalDamageMultiplier(character.getAttributes().combatAttributes.armor,
		currAttributes.combatAttributes.armorPenetration,
		currAttributes.combatAttributes.lethality);
	const int physicalDamage = currAttributes.combatAttributes.physicalDamage + bonusPhysicalDamage();
	const int damage = mult * (double)physicalDamage;

	// Deal damage.
	if(damage >= 0)
	{
		character.takeDamage(damage);
	}
}

Position Minion::firstVacantPathPosition()
{
	int currPositionNum = 0;

	for(int n = 0; n < path.size(); ++n)
	{
		GameSquare &square = *gameBoard.getSquare(path[n]);
		if(square.isVacant())
		{
			positionNum = n;
			return path[n];
		}
	}

	assert(false);  // Path entirely occupied. This should never occur.
	return {-1, -1};
}
