#include "VoidParalyseAbility.h"
#include <memory>
#include "Character.h"
#include "ParalyseEffect.h"
#include "HealthEffect.h"

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
	std::unique_ptr<Effect<EntityAttributes>> effect1 = std::make_unique<ParalyseEffect>(duration);

	const int level = getLevel() - 1;
	assert(level >= 0);
	const double multiplier = calculateAbilityMultiplier(*getCharacter(), target);
	const int damage = getTrueValue() * multiplier;
	std::unique_ptr<Effect<EntityAttributes>> effect2 = std::make_unique<HealthEffect>(1, -damage);

	target.addEffect(effect1);
	target.addEffect(effect2);

}

int VoidParalyseAbility::calculateCooldown() const
{
	return 12;
}
