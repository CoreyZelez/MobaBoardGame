#include <iostream>
#include <assert.h>
#include "Character.h"
#include "Minion.h"
#include "CharacterAttributesSystem.h"

Character::Character(GameBoard &gameBoard, std::vector< EntityAttributes> baseAttributes, 
	AbilityArsenal abilityArsenal, Team team, sf::Color left, sf::Color right)
	: GameEntity(team, ActiveEntityImage(team, left, right)), 
	gameBoard(gameBoard), 
	attributesSystem(*this, baseAttributes), 
	abilities(abilityArsenal)
{

}

void Character::init()
{
	const EntityAttributes &currAttributes = attributesSystem.getAttributes();
	const EntityAttributes &baseAttributes = attributesSystem.getBaseAttributes();
	abilities.initCharacter(*this);  // Grants each ability a reference to self.
	setHealth(currAttributes.healthAttributes.health, baseAttributes.healthAttributes.health); 
	spawn();
}

void Character::setLastDamaged(Character *character)
{
	assert(character != nullptr);
	lastDamaged = character;
}


void Character::update()
{
	attributesSystem.update();
	abilities.update();

	const EntityAttributes &currAttributes = attributesSystem.getAttributes();
	const EntityAttributes &baseAttributes = attributesSystem.getBaseAttributes();
	setHealth(currAttributes.healthAttributes.health, baseAttributes.healthAttributes.health);  // MUST BE RECALLED WHEN LEVELING UP!!!
}

const EntityAttributes &Character::getAttributes() const
{
	return attributesSystem.getAttributes();
}

const EntityAttributes &Character::getBaseAttributes() const
{
	return attributesSystem.getBaseAttributes();
}

int Character::getLevel() const
{
	return attributesSystem.getLevel();
}

int Character::getAbilityRange(int abilityNum) const
{
	return abilities.getAbilityRange(abilityNum);
}


bool Character::isAlive() const
{
	return attributesSystem.isAlive() > 0;
}

bool Character::unableToBasicAttack() const
{
	const EntityAttributes currAttributes = attributesSystem.getAttributes();
	const int points = currAttributes.actionAttributes.points;
	const int attackPoints = currAttributes.actionAttributes.attackPoints;
	const int attackCost = currAttributes.actionAttributes.attackCost;
	return (attackCost > points || attackCost > attackPoints);

}

bool Character::unableToUseAbility(int abilityNum) const
{
	const EntityAttributes currAttributes = attributesSystem.getAttributes();

	if(abilities.abilityIsOnCooldown(abilityNum))
	{
		return true;
	}

	const int points = currAttributes.actionAttributes.points;
	const int attackPoints = currAttributes.actionAttributes.attackPoints;
	const int pointCost = abilities.getAbilityPointCost(abilityNum);
	return (pointCost > points || pointCost > attackPoints);
}


bool Character::basicAttack(Character &target)
{
	EntityAttributes &currAttributes = attributesSystem.getAttributes();

	int &attackPoints = currAttributes.actionAttributes.attackPoints;
	int &points = currAttributes.actionAttributes.points;
	const int attackCost = currAttributes.actionAttributes.attackCost;
	const int range = currAttributes.actionAttributes.range;

	if(inRange(getPosition(), target.getPosition(), range)
		&& attackPoints >= attackCost && points >= attackCost)
	{
		notifyObservers(preBasicAttackDamageCalculation);
		notifyObservers(preBasicAttackDamageCalculation, target);

		// Update action points.
		attackPoints -= attackCost;
		points -= attackCost;

		// Calculate damage multiliers.
		const double basicAttackDamageMultiplier = getAttributes().specialAttributes.basicAttackDamageMultiplier;
		const double damageMultiplier = getAttributes().specialAttributes.damageMultiplier;
		const double priorMultiplier = basicAttackDamageMultiplier * damageMultiplier;  // Damage multiplier based on special attributes of character.
		const double mult = calculatePhysicalDamageMultiplier(target.getAttributes().combatAttributes.armor,
			currAttributes.combatAttributes.armorPenetration,
			currAttributes.combatAttributes.lethality) * priorMultiplier;

		// Deal damage.
		const int damage = mult * (double)currAttributes.combatAttributes.physicalDamage;
		int trueDamage;  // Damage that is actually dealt.
		assert(damage >= 0);
		target.lastDamaged = this;  

		notifyObservers(preBasicAttackDamageDealt);

		trueDamage = target.takeDamage(damage);

		notifyObservers(postBasicAttackDamageDealt);
		notifyObservers(postBasicAttackDamageDealt, trueDamage);
		notifyObservers(postBasicAttackDamageDealt, target);

		return true;
	}

	return false;
}

bool Character::basicAttack(Minion &target)
{
	EntityAttributes &currAttributes = attributesSystem.getAttributes();

	int &attackPoints = currAttributes.actionAttributes.attackPoints;
	int &points = currAttributes.actionAttributes.points;
	const int attackCost = currAttributes.actionAttributes.attackCost;
	const int range = currAttributes.actionAttributes.range;

	if(inRange(getPosition(), target.getPosition(), range)
		&& attackPoints >= attackCost && points >= attackCost)
	{
		notifyObservers(preBasicAttackDamageCalculation, target);

		// Update action points.
		attackPoints -= attackCost;
		points -= attackCost;

		// Deal damage.
		const double mult = calculatePhysicalDamageMultiplier(target.getAttributes().combatAttributes.armor,
			currAttributes.combatAttributes.armorPenetration,
			currAttributes.combatAttributes.lethality);
		const int damage = mult * (double)currAttributes.combatAttributes.physicalDamage;

		int experienceGain = 0;

		if(damage >= 0)
		{
			experienceGain = target.takeDamage(damage);  // Shouldnt return experience gain in future!! nearby allies get experience.
		}

		notifyObservers(postBasicAttackDamageDealt, target);

		return true;
	}

	return false;
}

void Character::printAttributes()
{
	const EntityAttributes currAttributes = attributesSystem.getAttributes();

	std::cout << std::endl;
	std::cout << getName() << std::endl;
	std::cout << "Health:         " << currAttributes.healthAttributes.health << std::endl;
	std::cout << "movementPoints: " << currAttributes.actionAttributes.movementPoints << std::endl;
	std::cout << "points:         " << currAttributes.actionAttributes.points << std::endl;
	std::cout << std::endl;

}

void Character::notifyObservers(CharacterAction action)
{
	for(auto &observer : observers)
	{
		observer->update(action);
	}
}

void Character::notifyObservers(CharacterAction action, int quantity)
{
	for(auto &observer : observers)
	{
		observer->update(action, quantity);
	}
}

void Character::notifyObservers(CharacterAction action, Character &character)
{
	for(auto &observer : observers)
	{
		observer->update(action, character);
	}
}

void Character::notifyObservers(CharacterAction action, Creature *creature)
{
	for(auto &observer : observers)
	{
		observer->update(action, creature);
	}
}

void Character::notifyObservers(CharacterAction action, Minion &minion)
{
	for(auto &observer : observers)
	{
		observer->update(action, minion);
	}
}

int Character::takeDamage(int damage)
{
	EntityAttributes &currAttributes = attributesSystem.getAttributes();
	assert(damage >= 0);

	int trueDamage = damage;
	if(damage > currAttributes.healthAttributes.health)
	{
		trueDamage = currAttributes.healthAttributes.health;
	}
	currAttributes.healthAttributes.health -= trueDamage;

	// Handles death.
	if(!isAlive())
	{
		deathReset();
	}

	return trueDamage;
}

void Character::addEffect(std::unique_ptr<EntityEffect> effect)
{
	attributesSystem.addEffect(std::move(effect));

	// Handles death.
	if(!this->isAlive())
	{
		this->deathReset();
		return;
	}
}

void Character::addStatusEffect(int duration, Status type)
{
	attributesSystem.addStatusEffect(duration, type);
}

bool Character::move(float x, float y)
{
	const Position targetPosition = gameBoard.getSquare(x, y)->getPosition();
	return move(targetPosition);
}

bool Character::move(Position position)
{
	EntityAttributes &currAttributes = attributesSystem.getAttributes();

	Position currPosition = getPosition();
	GameSquare *sourceSquare = gameBoard.getSquare(currPosition);
	GameSquare *targetSquare = gameBoard.getSquare(position);

	if(sourceSquare == targetSquare)
	{
		return false;
	}

	assert(sourceSquare->getOccupant() == this);  // Character position consistent with board.

	Position target = targetSquare->getPosition();

	if(targetSquare->isVacant())
	{
		std::list<Node> markedNodes = gameBoard.getMarkedNodes();
		auto it = std::find_if(markedNodes.begin(), markedNodes.end(), [target](Node node)
		{ return node.position == target; });

		if(it != markedNodes.end())
		{
			int cost = it->value;

			if(cost <= currAttributes.actionAttributes.movementPoints &&
				cost <= currAttributes.actionAttributes.points)
			{
				currAttributes.actionAttributes.movementPoints -= cost;
				currAttributes.actionAttributes.points -= cost;
				GameEntity::move(target);
				gameBoard.moveEntity(currPosition, target);

				assert(gameBoard.getSquare(target)->getOccupant() == this);
				assert(sourceSquare->isVacant());
				return true;
			}
		}
	}

	return false;
}

void Character::deathReset()
{
	attributesSystem.deathReset();
	spawn();

	notifyObservers(death);

	if(lastDamaged != nullptr)
	{
		lastDamaged->notifyObservers(kill, *this);
		lastDamaged = nullptr;
		// Characters should contain moneyInformation object that subscribes to character.
		// On the above notification, grants money.
	}
}

void Character::spawn()
{
	const Position currPosition = getPosition();
	GameSquare *currSquare = gameBoard.getSquare(currPosition);
	currSquare->removeOccupant();

	const Position spawnPosition = gameBoard.getSpawn(getTeam());

	for(int i = -1; i <= 1; ++i)
	{
		for(int j = -1; j <= 1; ++j)
		{
			const int x = spawnPosition.x + i;
			const int y = spawnPosition.y + j;
			Position position = { x, y };
			GameSquare *square = gameBoard.getSquare(position);
			if(square->isVacant())
			{
				square->setOccupant(this);
				GameEntity::move(position);
				return;
			}
		}
	}

	assert(false);  // No valid spawn found, game in error.
}

bool Character::useAbility(Character &target, int abilityNum)
{
	EntityAttributes &currAttributes = attributesSystem.getAttributes();

	const int abilityPointCost = abilities.getAbilityPointCost(abilityNum);  // Cost for attack points and points to cast ability.
	int &points = currAttributes.actionAttributes.points;
	int &attackPoints = currAttributes.actionAttributes.attackPoints;
	const int range = abilities.getAbilityRange(abilityNum);

	// Determines whether enough points and attack points to cast ability.
	if(abilityPointCost > points || abilityPointCost > attackPoints || !inRange(getPosition(), target.getPosition(), range))
	{
		return false;
	}

	// abilities.getAbility1Cost()  /// for mana if you choose to implement. then handle as required.
	bool successfulAbilityUse = abilities.useAbility(target, abilityNum);

	if(successfulAbilityUse)
	{
		points -= abilityPointCost;
		attackPoints -= abilityPointCost;
		return true;
	}

	return false;
}



bool Character::useAbility(Minion &target, int abilityNum)
{
	EntityAttributes &currAttributes = attributesSystem.getAttributes();

	const int abilityPointCost = abilities.getAbilityPointCost(abilityNum);  // Cost for attack points and points to cast ability.
	int &points = currAttributes.actionAttributes.points;
	int &attackPoints = currAttributes.actionAttributes.attackPoints;
	const int range = abilities.getAbilityRange(abilityNum);

	// Determines whether enough points and attack points to cast ability.
	if(abilityPointCost > points || abilityPointCost > attackPoints || !inRange(getPosition(), target.getPosition(), range))
	{
		return false;
	}

	// abilities.getAbility1Cost()  /// for mana if you choose to implement. then handle as required.
	bool successfulAbilityUse = abilities.useAbility(target, abilityNum);

	if(successfulAbilityUse)
	{
		points -= abilityPointCost;
		attackPoints -= abilityPointCost;
		return true;
	}

	return false;
}

void Character::subscribeObserver(CharacterObserver *observer)
{
	observers.push_back(observer);
}

void Character::unsubscribeObserver(CharacterObserver *observer)
{
	observers.remove(observer);
}

bool Character::hasEffectType(Status type)
{
	return attributesSystem.hasEffectType(type);
}




