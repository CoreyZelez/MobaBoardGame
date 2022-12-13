#include <memory>
#include "Ability.h"
#include "PassiveAbility.h"
#include "Character.h"
#include <iostream>


Ability::Ability(int range, int pointCost, double abilityPowerRatio)
	: range(range), pointCost(pointCost)
{
	abilityPowerRatios = { abilityPowerRatio , abilityPowerRatio , abilityPowerRatio };
}

Ability::Ability(int range, int pointCost, std::array<double, 3> abilityPowerRatios)
	: range(range), pointCost(pointCost), abilityPowerRatios(abilityPowerRatios)
{
}


int Ability::getLevel() const
{
	return level;
}

int Ability::getRange() const
{
	return range;
}

int Ability::getPointCost() const
{
	return pointCost;
}

bool Ability::onCooldown() const
{
	assert(cooldown >= 0);
	return cooldown > 0;
}

std::array<double, 3> Ability::getAbilityPowerRatios() const
{
	return abilityPowerRatios;
}



void Ability::initCharacter(Character &character)
{
	this->character = &character;
	character.subscribeObserver(this);
}


bool Ability::use(Character &target)
{
	if(validTarget(target) && cooldown == 0 && level > 0)
	{
		applyTarget(target);
		applySelf();
		cooldown = calculateCooldown();
		return true;
	}

	return false;
}

void Ability::reduceCooldown()
{
	assert(cooldown >= 0);

	if(cooldown > 0)
	{
		--cooldown;
	}
}



int Ability::getTrueAbilityPower() const
{
	const int level = this->level - 1;
	const int abilityPower = character->getAttributes().abilityAttributes.abilityPower;
	return abilityPower * abilityPowerRatios[level];
}

int Ability::getTrueAbilityPower(Character &target) const
{
	return getTrueAbilityPower() * calculateAbilityMultiplier(*character, target);
}

Character *const Ability::getCharacter()
{
	return character;
}




