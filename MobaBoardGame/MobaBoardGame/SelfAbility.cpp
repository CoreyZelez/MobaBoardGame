#include "SelfAbility.h"



SelfAbility::SelfAbility(std::array<double, 3> levelValues)
	: Ability(levelValues, 0)
{
}

SelfAbility::SelfAbility(std::array<double, 3> levelValues, double abilityPowerRatio)
	: Ability(levelValues, 0, abilityPowerRatio)
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
