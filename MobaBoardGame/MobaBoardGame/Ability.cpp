#include <memory>
#include "Ability.h"
#include "PassiveAbility.h"
#include "EmptyPassive.h"
#include "Character.h"


Ability::Ability(std::array<double, 3> levelValues, int range)
	: levelValues(levelValues), range(range)
{
}

Ability::Ability(std::array<double, 3> levelValues, int range, double abilityPowerRatio)
	: levelValues(levelValues), range(range), abilityPowerRatio(abilityPowerRatio)
{
}

int Ability::getLevel() const
{
	return level;
}



void Ability::initCharacter(Character &character)
{
	this->character = &character;
	character.subscribeObserver(this);
}



std::array<double, 3> Ability::getLevelValues() const
{
	return levelValues;
}

int Ability::getTrueValue()
{
	const int abilityPower = character->getAttributes().abilityAttributes.abilityPower;
	const int level = getLevel() - 1;
	return levelValues[level] + (abilityPowerRatio * abilityPower);
}

double Ability::getAbilityPowerRatio() const
{
	return abilityPowerRatio;
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



Character *const Ability::getCharacter()
{
	return character;
}




