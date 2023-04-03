#include "CharacterAbilities.h"
#include <iostream>

CharacterAbilities::CharacterAbilities(AbilityArsenal arsenal)
	: passive(arsenal.passive->clone())
{
	for(auto &ability : arsenal.abilities)
	{
		abilities.push_back(ability->clone());
	}
}

void CharacterAbilities::initCharacter(Character &character)
{
	passive.get()->initCharacter(character);
	for(auto &ability : abilities)
	{
		ability.get()->initCharacter(character);
	}
}

void CharacterAbilities::update()
{
	passive.get()->apply();

	for(auto &ability : abilities)
	{
		ability.get()->update();
		ability.get()->reduceCooldown();
	}
}

int CharacterAbilities::getAbilityRange(int abilityNum) const
{
	const int abilityIndex = abilityNum - 1;
	return abilities[abilityIndex].get()->getRange();
}

int CharacterAbilities::getAbilityPointCost(int abilityNum) const
{
	const int abilityIndex = abilityNum - 1;
	return abilities[abilityIndex].get()->getPointCost();
}


bool CharacterAbilities::abilityIsOnCooldown(int abilityNum) const
{
	const int abilityIndex = abilityNum - 1;
	return abilities[abilityIndex].get()->onCooldown();
}


bool CharacterAbilities::useAbility(Character &target, int abilityNum)
{
	const int abilityIndex = abilityNum - 1;
	return abilities[abilityIndex].get()->use(target);
}

bool CharacterAbilities::useAbility(Minion &target, int abilityNum)
{
	const int abilityIndex = abilityNum - 1;
	return abilities[abilityIndex].get()->use(target);
}
