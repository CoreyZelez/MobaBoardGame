#include <iostream>
#include "Character.h"

const std::array<int, 8> Character::experienceForLevel = { 0, 20, 45, 80, 130, 200, 300, 450 };

Character::Character(Position position, std::array<const CharacterAttributes, 8> baseAttributes, AbilityArsenal abilityArsenal)
	: position(position), baseAttributes(baseAttributes), abilities(abilityArsenal)
{
	currAttributes = baseAttributes[0];  // Current attributes starts at level 0 base attributes.
	abilities.initCharacter(*this);  // Grants each ability a reference to self.
}

void Character::update()
{
	updateCurrAttributes();
	effects.update(currAttributes);  // Applys each effect and updates them.
}

CharacterAttributes Character::getAttributes()
{
	return currAttributes;
}

void Character::basicAttack(Character &enemy)
{
	if(inRange(position, enemy.position, currAttributes.actionAttributes.range))
	{
		notifyObservers(preBasicAttackCharacter);

		// Update action points.
		currAttributes.actionAttributes.attackPoints -= currAttributes.actionAttributes.attackCost;
		currAttributes.actionAttributes.points -= currAttributes.actionAttributes.attackCost;

		// Deal damage.
		enemy.notifyObservers(preTakeCharacterDamage);
		double mult = calculatePhysicalDamageMultiplier(enemy.currAttributes.combatAttributes.armor,
			currAttributes.combatAttributes.armorPenetration,
			currAttributes.combatAttributes.lethality);
		enemy.currAttributes.healthAttributes.health -= currAttributes.combatAttributes.physicalDamage * mult;
	}
}

void Character::printAttributes()
{
	std::cout << "Health:   " << currAttributes.healthAttributes.health << std::endl;
	std::cout << "Movement: " << currAttributes.actionAttributes.movementPoints << std::endl;
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

void Character::addEffect(std::unique_ptr<CharacterEffect> &effect)
{
	// Applys effect and updates it.
	effect.get()->update(currAttributes);

	// Adds effect if duration not 0 after initial update.
	if(!effect.get()->isOver())
	{
		effects.add(effect);
	}
}

void Character::subscribeObserver(CharacterObserver *observer)
{
	observers.push_back(observer);
}

void Character::unsubscribeObserver(CharacterObserver *observer)
{
	observers.remove(observer);
}

double calculatePhysicalDamageMultiplier(int armor, int armorPenetration, int lethality)
{
	int trueArmor = ((armor * armorPenetration) / 100) - lethality;
	double multiplier;

	if(trueArmor >= 0)
	{
		multiplier = 100 / (100 + trueArmor);
	}
	else
	{
		multiplier = 2 - (100 / 100 - armor);
	}

	return multiplier;
}
