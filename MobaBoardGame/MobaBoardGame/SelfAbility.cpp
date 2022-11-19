#include "SelfAbility.h"

SelfAbility::SelfAbility(PassiveAbility *passive)
	: Ability(passive)
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
