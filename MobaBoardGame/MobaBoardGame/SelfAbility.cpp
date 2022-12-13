#include "SelfAbility.h"


SelfAbility::SelfAbility(int pointCost, std::array<double, 3> abilityPowerRatios)
	: Ability(0, pointCost, abilityPowerRatios)
{
}

SelfAbility::SelfAbility(int pointCost, double abilityPowerRatio)
	: Ability(0, pointCost, abilityPowerRatio)
{
}

bool SelfAbility::validTarget(Character &target)
{
	if(&target == getCharacter())
	{
		return true;
	}

	return false;
}
