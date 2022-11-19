#include "LifeStealPassive.h"
#include "CharacterAction.h"

void LifeStealPassive::update(CharacterAction action)
{
	if(action == basicAttackCharacter)
	{
		incrementStacks(1);
	}
}

void LifeStealPassive::incrementStacks(int amount)
{
	stacks += amount;
}

std::unique_ptr<PassiveAbility> LifeStealPassive::clone()
{
	return std::make_unique<LifeStealPassive>(*this);
}
