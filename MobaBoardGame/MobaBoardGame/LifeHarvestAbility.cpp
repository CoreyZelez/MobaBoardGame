#include <memory>
#include <iostream>
#include "LifeHarvestAbility.h"
#include "HealthDrainEffect.h"
#include "Character.h"

LifeHarvestAbility::LifeHarvestAbility(std::array<double, 3> damageValues)
	: Ability(3, 2, 0.5), damageValues(damageValues)
{

}

std::unique_ptr<Ability> LifeHarvestAbility::clone()
{
	return std::make_unique<LifeHarvestAbility>(damageValues);
}

bool LifeHarvestAbility::validTarget(Character &character)
{
	return &character != getCharacter();
}

void LifeHarvestAbility::applyTarget(Character &target) 
{
	if(getLevel() == 0)
	{
		return;
	}

	const int abilityPower = getCharacter()->getAttributes().abilityAttributes.abilityPower;
	const double multiplier = calculateAbilityMultiplier(*getCharacter(), target);

	// Determines damage amount.
	const int level = getLevel() - 1;
	const int amount = (damageValues[level] * multiplier) + (getTrueAbilityPower());
	std::cout << damageValues[level] << "    " << getTrueAbilityPower() << std::endl;
	std::cout << std::endl << multiplier << "      " <<"amoUNT >" << amount << std::endl;

	// Determines drainRate
	double absorbRatio;  // Percent of health drained that is "harvested".
	switch(getLevel())
	{
	case 1:
		absorbRatio = 0.6;
		break;
	case 2:
		absorbRatio = 0.8;
		break;
	case 3:
		absorbRatio = 1;
		break;
	}

	const int damagePerTurn = (double)amount / (double)duration;
	std::unique_ptr<Effect<EntityAttributes>> effect = std::make_unique<HealthDrainEffect>(duration, damagePerTurn, absorbRatio, *getCharacter());
	target.addEffect(effect);
}

int LifeHarvestAbility::calculateCooldown() const
{
	return 10;
}
