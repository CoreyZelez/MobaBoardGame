#include "MinionAttributesSystem.h"
#include "MinionEffectsManager.h"
#include <iostream>

MinionAttributesSystem::MinionAttributesSystem(Minion &minion, EntityAttributes baseAttributes)
	: effects(minion), minion(minion), baseAttributes(baseAttributes)
{
	const int arrayLevel = level - 1;
	assert(arrayLevel == 0);  // Can remove for testing purposes.
	currAttributes = baseAttributes[arrayLevel];  // Current attributes starts at level 0 base attributes.
}

EntityAttributes& MinionAttributesSystem::getAttributes()
{
	return currAttributes;
}

EntityAttributes MinionAttributesSystem::getAttributes() const
{
	return currAttributes;
}

EntityAttributes MinionAttributesSystem::getBaseAttributes() const
{
	const int adjustedLevel = level - 1;
	return baseAttributes[adjustedLevel];
}

int MinionAttributesSystem::getLevel() const
{
	return level;
}

void MinionAttributesSystem::update()
{
	resetCurrAttributes();
	effects.update();
}

bool MinionAttributesSystem::isAlive() const
{
	return currAttributes.healthAttributes.health > 0;
}

bool MinionAttributesSystem::hasEffectType(Status type) const
{
	return effects.hasEffectType(type);
}

void MinionAttributesSystem::addEffect(std::unique_ptr<EntityEffect>& effect)
{
	// Applys effect and updates it.
	effect.get()->update(currAttributes);


	// Adds effect if duration not 0 after initial update.
	if(!effect.get()->isOver())
	{
		effects.add(effect);
	}
}

void MinionAttributesSystem::addStatusEffect(int duration, Status type)
{
	effects.add(duration, type);
}

void MinionAttributesSystem::reset()
{
	assert(currAttributes.healthAttributes.health <= 0);

	const int level = getLevel() - 1;
	currAttributes = baseAttributes[level];

	effects.clear();
}

void MinionAttributesSystem::resetCurrAttributes()
{
	const int level = getLevel() - 1;
	const int health = currAttributes.healthAttributes.health;  // Health is not recalculated.
	currAttributes = baseAttributes[level];
	assert(health <= currAttributes.healthAttributes.health);  // Health cannot be more than base health.
	currAttributes.healthAttributes.health = health;
}
