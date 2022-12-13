#include "VoidParalyseAbility.h"
#include <memory>
#include "Character.h"
#include "ParalyseEffect.h"
#include "HealthEffect.h"
#include "MovementPointEffect.h"
#include "ActionPointEffect.h"


VoidParalyseAbility::VoidParalyseAbility(std::array<double, 3> damageValues)
	: Ability(1, 2, 0.5), damageValues(damageValues)
{
}

std::unique_ptr<Ability> VoidParalyseAbility::clone()
{
	return std::make_unique<VoidParalyseAbility>(damageValues);
}

bool VoidParalyseAbility::validTarget(Character &character)
{
	if(&character != getCharacter())
	{
		return true;
	}

	return false;
}

void VoidParalyseAbility::applyTarget(Character &target)
{
	std::unique_ptr<Effect<EntityAttributes>> effect1 = std::make_unique<ParalyseEffect>(duration);

	const int level = getLevel() - 1;
	assert(level >= 0);
	const double multiplier = calculateAbilityMultiplier(*getCharacter(), target);
	const int trueAbilityPower = getTrueAbilityPower(target); 
	const int damage = (multiplier * damageValues[level]) + trueAbilityPower;
	const int maxHealth = target.getBaseAttributes().healthAttributes.health;
	std::unique_ptr<Effect<EntityAttributes>> effect2 = std::make_unique<HealthEffect>(1, -damage, maxHealth);

	target.addEffect(effect1);
	target.addEffect(effect2);

	target.addStatusEffect(duration, voidInfliction);

}

void VoidParalyseAbility::applySelf()
{
	// Makes it easier for player to escape.
	std::unique_ptr<Effect<EntityAttributes>> effect1 = std::make_unique<MovementPointEffect>(1, 1);  // Gain 1 movement point.
	std::unique_ptr<Effect<EntityAttributes>> effect2 = std::make_unique<ActionPointEffect>(1, 1);  // Gain 1 action point.

}

int VoidParalyseAbility::calculateCooldown() const
{
	return 13;
}
