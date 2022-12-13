#include <iostream>
#include "Character.h"
#include "CharacterAttributesSystem.h"

Character::Character(GameBoard &gameBoard, std::array<const EntityAttributes, 6> baseAttributes, 
	AbilityArsenal abilityArsenal, Team team, sf::Color left, sf::Color right)
	: GameEntity(team, left, right), 
	gameBoard(gameBoard), 
	attributesSystem(*this, baseAttributes), 
	abilities(abilityArsenal)
{

}

void Character::init()
{
	EntityAttributes &currAttributes = attributesSystem.getAttributes();
	const EntityAttributes baseAttributes = attributesSystem.getBaseAttributes();
	abilities.initCharacter(*this);  // Grants each ability a reference to self.
	setHealth(currAttributes.healthAttributes.health, baseAttributes.healthAttributes.health);  // MUST BE RECALLED WHEN LEVELING UP!!!
	spawn();
	std::cout << currAttributes.healthAttributes.health << " " << baseAttributes.healthAttributes.health << std::endl;
}

void Character::setLastDamaged(Character *character)
{
	assert(character != nullptr);
	lastDamaged = character;
}


void Character::update()
{
	// MOVE TO ATTRIBUTES SYSTEM START
	/// updateCurrAttributes();
	/// effects.update(*this, currAttributes);  // Applys each effect and updates them.  /// Make effects hold charcter refernce rather than using parameters.
	// MOVE TO ATTRIBUTES SYSTEM END.

	attributesSystem.update();

	abilities.update();
	// printAttributes();
}

EntityAttributes & Character::getAttributes()
{
	return attributesSystem.getAttributes();
}

EntityAttributes Character::getAttributes() const
{
	return attributesSystem.getAttributes();
}

EntityAttributes Character::getBaseAttributes() const
{
	return attributesSystem.getBaseAttributes();

}

int Character::getLevel() const
{
	return attributesSystem.getLevel();
}

int Character::getAbility1Range() const
{
	return abilities.getAbility1Range();
}

int Character::getAbility2Range() const
{
	return abilities.getAbility2Range();
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

bool Character::unableToUseAbility1() const
{
	const EntityAttributes currAttributes = attributesSystem.getAttributes();

	if(abilities.ability1IsOnCooldown())
	{
		return true;
	}

	const int points = currAttributes.actionAttributes.points;
	const int attackPoints = currAttributes.actionAttributes.attackPoints;
	const int pointCost = abilities.getAbility1PointCost();
	return (pointCost > points || pointCost > attackPoints);
}

bool Character::unableToUseAbility2() const
{
	const EntityAttributes currAttributes = attributesSystem.getAttributes();

	if(abilities.ability2IsOnCooldown())
	{
		return true;
	}
	const int points = currAttributes.actionAttributes.points;
	const int attackPoints = currAttributes.actionAttributes.attackPoints;
	const int pointCost = abilities.getAbility2PointCost();
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
		notifyObservers(preBasicAttackCharacter, target);

		// Update action points.
		attackPoints -= attackCost;
		points -= attackCost;

		// Deal damage.
		const double mult = calculatePhysicalDamageMultiplier(target.getAttributes().combatAttributes.armor,
			currAttributes.combatAttributes.armorPenetration,
			currAttributes.combatAttributes.lethality);
		const int damage = mult * (double)currAttributes.combatAttributes.physicalDamage;

		if(damage >= 0)
		{
			target.lastDamaged = this;  
			target.takeDamage(damage);
		}

		notifyObservers(postBasicAttackCharacter, target);

		// Handles death.
		if(!target.isAlive())
		{
			target.deathReset();
		}

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

void Character::notifyObservers(TargetCharacterAction action, Character &character)
{
	if(action == killCharacter)
	{
		std::cout << std::endl << "YOU KILL A CHARACTER!!" << std::endl;
	}
	for(auto &observer : observers)
	{
		observer->update(action, character);
	}
}

void Character::notifyObservers(TargetCreatureAction action, Creature *creature)
{
	for(auto &observer : observers)
	{
		observer->update(action, creature);
	}
}

void Character::takeDamage(int damage)
{
	EntityAttributes &currAttributes = attributesSystem.getAttributes();
	assert(damage >= 0);
	notifyObservers(preReceiveCharacterBasicAttack);
	currAttributes.healthAttributes.health -= damage;
	notifyObservers(postReceiveCharacterBasicAttack);
}

void Character::addEffect(std::unique_ptr<EntityEffect> &effect)
{
	attributesSystem.addEffect(effect);

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

bool Character::move(Position position, int cost)
{
	EntityAttributes &currAttributes = attributesSystem.getAttributes();

	if(cost <= currAttributes.actionAttributes.movementPoints &&
		cost <= currAttributes.actionAttributes.points)
	{
		currAttributes.actionAttributes.movementPoints -= cost;
		currAttributes.actionAttributes.points -= cost;
		GameEntity::move(position);
		return true;
	}

	return false;
}

void Character::deathReset()
{
	attributesSystem.reset();
	spawn();

	notifyObservers(death);

	if(lastDamaged != nullptr)
	{
		lastDamaged->notifyObservers(killCharacter, *this);
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

	GameSquare *spawnSquare = gameBoard.getSquare(spawnPosition);
	assert(spawnSquare->isVacant());
	spawnSquare->setOccupant(this);

	GameEntity::move(spawnPosition);
}

bool Character::useAbility1(Character &target)
{
	EntityAttributes &currAttributes = attributesSystem.getAttributes();

	const int abilityPointCost = abilities.getAbility1PointCost();  // Cost for attack points and points to cast ability.
	int &points = currAttributes.actionAttributes.points;
	int &attackPoints = currAttributes.actionAttributes.attackPoints;
	const int range = abilities.getAbility1Range();

	// Determines whether enough points and attack points to cast ability.
	if(abilityPointCost > points || abilityPointCost > attackPoints || !inRange(getPosition(), target.getPosition(), range))
	{
		return false;
	}

	// abilities.getAbility1Cost()  /// for mana if you choose to implement. then handle as required.
	bool successfulAbilityUse = abilities.useAbility1(target);

	if(successfulAbilityUse)
	{
		points -= abilityPointCost;
		attackPoints -= abilityPointCost;
		return true;
	}

	return false;
}

bool Character::useAbility2(Character &target)
{
	EntityAttributes &currAttributes = attributesSystem.getAttributes();

	const int abilityPointCost = abilities.getAbility2PointCost();  // Cost for attack points and points to cast ability.
	int &points = currAttributes.actionAttributes.points;
	int &attackPoints = currAttributes.actionAttributes.attackPoints;
	const int range = abilities.getAbility2Range();

	// Determines whether enough points and attack points to cast ability.
	if(abilityPointCost > points || abilityPointCost > attackPoints || !inRange(getPosition(), target.getPosition(), range))
	{
		return false;
	}

	// abilities.getAbility1Cost()  /// for mana if you choose to implement. then handle as required.
	bool successfulAbilityUse = abilities.useAbility2(target);

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




