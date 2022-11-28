#include "VoidParalyseAbility.h"
#include <memory>
#include "Character.h"
#include "ParalyseEffect.h"
#include "HealthEffect.h"
#include "MovementPointEffect.h"
#include "ActionPointEffect.h"


VoidParalyseAbility::VoidParalyseAbility(std::array<double, 3> levelValues, int duration)
	: Ability(levelValues, 1, 0.5), duration(duration)
{
}

std::unique_ptr<Ability> VoidParalyseAbility::clone()
{
	return std::make_unique<VoidParalyseAbility>(getLevelValues(), duration);
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
	std::unique_ptr<Effect<EntityAttributes>> effect1 = std::make_unique<ParalyseEffect>(duration, voidInfliction);

	const int level = getLevel() - 1;
	assert(level >= 0);
	const double multiplier = calculateAbilityMultiplier(*getCharacter(), target);
	const int damage = getTrueValue() * multiplier;
	std::unique_ptr<Effect<EntityAttributes>> effect2 = std::make_unique<HealthEffect>(1, -damage);

	target.addEffect(effect1);
	target.addEffect(effect2);

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
