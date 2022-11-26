#include <iostream>
#include "Character.h"

Character::Character(Position position, std::array<const EntityAttributes, 6> baseAttributes, AbilityArsenal abilityArsenal)
	: position(position), baseAttributes(baseAttributes), abilities(abilityArsenal)
{

}

void Character::init()
{
	// const int level = levelInformation.level - 1;  // Should be 0 under normal circumstances.
	const int level = 5;  // Should be 0 under normal circumstances.
	currAttributes = baseAttributes[level];  // Current attributes starts at level 0 base attributes.
	abilities.initCharacter(*this);  // Grants each ability a reference to self.
}

void Character::initName(std::string name)
{
	this->name = name;
}

void Character::update()
{
	updateCurrAttributes();
	effects.update(currAttributes);  // Applys each effect and updates them.
	abilities.update();
}

EntityAttributes Character::getAttributes() const
{
	return currAttributes;
}

EntityAttributes Character::getBaseAttributes() const
{
	const int level = getLevel() - 1;
	return baseAttributes[level];
}

int Character::getLevel() const
{
	return levelInformation.level;
}

void Character::basicAttack(Character &target)
{
	if(inRange(position, target.position, currAttributes.actionAttributes.range))
	{
		notifyObservers(preBasicAttackCharacter, target);

		// Update action points.
		currAttributes.actionAttributes.attackPoints -= currAttributes.actionAttributes.attackCost;
		currAttributes.actionAttributes.points -= currAttributes.actionAttributes.attackCost;

		// Deal damage.
		const double mult = calculatePhysicalDamageMultiplier(target.currAttributes.combatAttributes.armor,
			currAttributes.combatAttributes.armorPenetration,
			currAttributes.combatAttributes.lethality);
		const int damage = mult * (double)currAttributes.combatAttributes.physicalDamage;
		std::cout << std::endl;
		std::cout << target.getAttributes().healthAttributes.health;
		target.takeDamage(damage);
		std::cout << " --- " << target.getAttributes().healthAttributes.health << std::endl;
		std::cout << std::endl;


		notifyObservers(postBasicAttackCharacter, target);
	}
}

void Character::printAttributes()
{
	std::cout << std::endl;
	std::cout << name << std::endl;
	std::cout << "Health:         " << currAttributes.healthAttributes.health << std::endl;
	std::cout << "movementPoints: " << currAttributes.actionAttributes.movementPoints << std::endl;
	std::cout << "points:         " << currAttributes.actionAttributes.points << std::endl;
	std::cout << std::endl;

}

void Character::updateCurrAttributes()
{
	const int health = currAttributes.healthAttributes.health;  // Health is not recalculated.
	currAttributes = baseAttributes[levelInformation.level];
	currAttributes.healthAttributes.health = health;
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
	notifyObservers(preReceiveCharacterBasicAttack);
	currAttributes.healthAttributes.health -= damage;
	notifyObservers(postReceiveCharacterBasicAttack);
}

void Character::addEffect(std::unique_ptr<EntityEffect> &effect)
{
	// Applys effect and updates it.
	effect.get()->update(currAttributes);

	// Adds effect if duration not 0 after initial update.
	if(!effect.get()->isOver())
	{
		effects.add(effect);
	}
}

void Character::useAbility1(Character &target)
{
	abilities.useAbility1(target);
}

void Character::useAbility2(Character & target)
{
	abilities.useAbility2(target);
}

void Character::subscribeObserver(CharacterObserver *observer)
{
	observers.push_back(observer);
}

void Character::unsubscribeObserver(CharacterObserver *observer)
{
	observers.remove(observer);
}
