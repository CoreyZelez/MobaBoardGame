#include "CharacterAttributesSystem.h"
#include "CharacterEffectsManager.h"
#include <iostream>

CharacterAttributesSystem::CharacterAttributesSystem(Character &character, std::array<const EntityAttributes, 6> baseAttributes)
	: effects(character), character(character), baseAttributes(baseAttributes)
{
	const int arrayLevel = level - 1;
	assert(arrayLevel == 0);  // Can remove for testing purposes.
	currAttributes = baseAttributes[arrayLevel];  // Current attributes starts at level 0 base attributes.
}

EntityAttributes& CharacterAttributesSystem::getAttributes()
{
	return currAttributes;
}

EntityAttributes CharacterAttributesSystem::getAttributes() const
{
	return currAttributes;
}

EntityAttributes CharacterAttributesSystem::getBaseAttributes() const
{
	const int adjustedLevel = level - 1;
	return baseAttributes[adjustedLevel];
}

int CharacterAttributesSystem::getLevel() const
{
	return level;
}

void CharacterAttributesSystem::update()
{
	updateCurrAttributes();
	effects.update();
}

bool CharacterAttributesSystem::isAlive() const
{
	return currAttributes.healthAttributes.health > 0;
}

bool CharacterAttributesSystem::hasEffectType(Status type) const
{
	return effects.hasEffectType(type);
}

void CharacterAttributesSystem::addEffect(std::unique_ptr<EntityEffect>& effect)
{
	// Applys effect and updates it.
	effect.get()->update(currAttributes);


	// Adds effect if duration not 0 after initial update.
	if(!effect.get()->isOver())
	{
		effects.add(effect);
	}
}

void CharacterAttributesSystem::addStatusEffect(int duration, Status type)
{
	effects.add(duration, type);
}

void CharacterAttributesSystem::reset()
{
	assert(currAttributes.healthAttributes.health <= 0);

	const int level = getLevel() - 1;
	currAttributes = baseAttributes[level];

	effects.clear();
}

void CharacterAttributesSystem::resetCurrAttributes()
{
	const int level = getLevel() - 1;
	const int health = currAttributes.healthAttributes.health;  // Health is not recalculated.
	currAttributes = baseAttributes[level];
	assert(health <= currAttributes.healthAttributes.health);  // Health cannot be more than base health.
	currAttributes.healthAttributes.health = health;
}
