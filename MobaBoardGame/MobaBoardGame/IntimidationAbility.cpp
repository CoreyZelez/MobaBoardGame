#include "IntimidationAbility.h"
#include "TargetedDamageReductionEffect.h"
#include "Character.h"
#include "HealthEffect.h"

IntimidationAbility::IntimidationAbility()
	: Ability(2, 2, 1), damageReductionRatios({ 0.3, 0.4, 0.5 }), healthChangeValues({ 60, 110, 185 })
{
}

IntimidationAbility::IntimidationAbility(std::array<double, 3> damageReductionRatios, std::array<double, 3> healthChangeValues)
	: Ability(2, 2, 1), damageReductionRatios(damageReductionRatios), healthChangeValues(healthChangeValues)
{
}

std::unique_ptr<Ability> IntimidationAbility::clone()
{
	return std::make_unique<IntimidationAbility>(damageReductionRatios, healthChangeValues);
}

bool IntimidationAbility::validTarget(Character &target)
{
	return target.getTeam() != getCharacter()->getTeam();
}

void IntimidationAbility::applyTarget(Character &target)
{
	const int level = getLevel() - 1;
	std::unique_ptr<Effect<EntityAttributes>> effect = 
		std::make_unique<TargetedDamageReductionEffect>(5, damageReductionRatios[level], *getCharacter(), target);
	target.addEffect(std::move(effect));
}

void IntimidationAbility::applySelf()
{
	const int level = getLevel() - 1; 
	std::unique_ptr<Effect<EntityAttributes>> effect = std::make_unique<HealthEffect>(1, healthChangeValues[level], *getCharacter()); 
	getCharacter()->addEffect(std::move(effect));
} 

int IntimidationAbility::calculateCooldown() const
{
	return 19;
}
