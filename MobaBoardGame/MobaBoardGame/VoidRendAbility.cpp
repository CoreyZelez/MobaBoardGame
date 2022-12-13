#include "VoidRendAbility.h"
#include "Character.h"
#include "PhysicalDamageEffect.h"
#include "ArmorEffect.h"
#include <iostream>

/* Level values are for physicalAttack reduction applied to target. */
VoidRendAbility::VoidRendAbility(std::array<double, 3> statChangeValues)
	: Ability(4, 2, 0.5), statChangeValues(statChangeValues)
{
}

std::unique_ptr<Ability> VoidRendAbility::clone()
{
	return std::make_unique<VoidRendAbility>(statChangeValues);
}

void VoidRendAbility::update(TargetCharacterAction action, Character &target)
{

}

bool VoidRendAbility::validTarget(Character &target)
{
	return &target != getCharacter();
}

void VoidRendAbility::applyTarget(Character &target)
{
	const int level = getLevel() - 1;
	assert(level >= 0);

	// Calculation of effects on target.
	const double multiplier = calculateAbilityMultiplier(*getCharacter(), target);
	int amount = getTrueAbilityPower(target) + (statChangeValues[level] * multiplier);
	int pdAmount = -amount;
	int armorAmount = -amount * armorMultiplier;
	// Adds effects to target.
	std::unique_ptr<Effect<EntityAttributes>> effect1 = std::make_unique<PhysicalDamageEffect>(duration, pdAmount);
	std::unique_ptr<Effect<EntityAttributes>> effect2 = std::make_unique<ArmorEffect>(duration, armorAmount);
	target.addEffect(effect1);
	target.addEffect(effect2);

	target.addStatusEffect(duration, voidInfliction);


	// Absorption of stats for self.
	armorAmount = amount * selfMultiplier;
	pdAmount = amount *selfMultiplier;
	std::unique_ptr<Effect<EntityAttributes>> effect3 = std::make_unique<PhysicalDamageEffect>(duration, pdAmount);
	std::unique_ptr<Effect<EntityAttributes>> effect4 = std::make_unique<ArmorEffect>(duration, selfMultiplier);
	getCharacter()->addEffect(effect3);
	getCharacter()->addEffect(effect4);
}

int VoidRendAbility::calculateCooldown() const
{
	return 17;
}
