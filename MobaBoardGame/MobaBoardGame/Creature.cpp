#include "Creature.h"
#include "Character.h"

Creature::Creature(std::array<const EntityAttributes, 6> baseAttributes, sf::Color left, sf::Color right)
	: GameEntity(neutral, left, right), baseAttributes(baseAttributes)
{
}

void Creature::attack(Character &target)
{
	int &attackPoints = currAttributes.actionAttributes.attackPoints;
	int &points = currAttributes.actionAttributes.points;
	const int attackCost = currAttributes.actionAttributes.attackCost;
	const int range = currAttributes.actionAttributes.range;

	if(inRange(getPosition(), target.getPosition(), range)
		&& attackPoints >= attackCost && points >= attackCost)
	{
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
			target.takeDamage(damage);
		}

		// Handles death.
		if(!target.isAlive())
		{
			target.deathReset();
		}
	}
}

void Creature::updateCurrAttributes()
{
	const int level = this->level - 1;
	const int health = currAttributes.healthAttributes.health;  // Health is not recalculated.
	currAttributes = baseAttributes[level];
	assert(health <= currAttributes.healthAttributes.health);  // Health cannot be more than base health.
	currAttributes.healthAttributes.health = health;
}

EntityAttributes Creature::getCurrAttributes()
{
	return currAttributes;
}
