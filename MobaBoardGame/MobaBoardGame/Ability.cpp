#include <memory>
#include "Ability.h"
#include "PassiveAbility.h"
#include "EmptyPassive.h"
#include "Character.h"


Ability::Ability(std::array<int, 3> levelValues, int range)
	: levelValues(levelValues), range(range), passive(std::make_unique<EmptyPassive>(EmptyPassive()))
{
}

Ability::Ability(std::array<int, 3> levelValues, int range, PassiveAbility *passive)
	: levelValues(levelValues), range(range), passive(passive->clone())
{
}

int Ability::getLevel() const
{
	return level;
}

void Ability::initCharacter(Character & character)
{
	passive.get()->initCharacter(character);
	character.subscribeObserver(passive.get());
}

std::array<int, 3> Ability::getLevelValues() const
{
	return levelValues;
}

bool Ability::use(Character &target)
{
	if(validTarget(target))
	{
		applyTarget(target);
		applySelf();
		cooldown = calculateCooldown();
		return true;
	}

	return false;
}

void Ability::applyPassive()
{
	passive.get()->apply();
}

Character* Ability::getOwner()
{
	return passive.get()->getCharacter();
}




