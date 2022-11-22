#include "SelfAbility.h"

SelfAbility::SelfAbility(std::array<int, 3> coreValues, PassiveAbility *passive)
	: Ability(coreValues, 0, passive)
{
}

SelfAbility::SelfAbility(std::array<int, 3> coreValues)
	: Ability(coreValues, 0)
{
}

bool SelfAbility::validTarget(Character &target)
{
	if(&target == getOwner())
	{
		return true;
	}

	return false;
}
