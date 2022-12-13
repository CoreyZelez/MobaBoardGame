#include "CharacterAbilities.h"
#include <iostream>

CharacterAbilities::CharacterAbilities(AbilityArsenal arsenal)
	: passive(arsenal.passive->clone()),
	ability1(arsenal.ability1->clone()),
	ability2(arsenal.ability2->clone())
{
}

void CharacterAbilities::initCharacter(Character &character)
{
	passive.get()->initCharacter(character);
	ability1.get()->initCharacter(character);
	ability2.get()->initCharacter(character);
}

void CharacterAbilities::update()
{
	passive.get()->apply();
	ability1.get()->update();
	ability2.get()->update();
	ability1.get()->reduceCooldown();
	ability2.get()->reduceCooldown();
}

int CharacterAbilities::getAbility1Range() const
{
	return ability1.get()->getRange();
}

int CharacterAbilities::getAbility2Range() const
{
	return ability2.get()->getRange();
}

int CharacterAbilities::getAbility1PointCost() const
{
	return ability1.get()->getPointCost();
}

int CharacterAbilities::getAbility2PointCost() const
{
	return ability2.get()->getPointCost();
}

bool CharacterAbilities::ability1IsOnCooldown() const
{
	return ability1.get()->onCooldown();
}

bool CharacterAbilities::ability2IsOnCooldown() const
{
	return ability2.get()->onCooldown();
}

bool CharacterAbilities::useAbility1(Character & target)
{
	return ability1.get()->use(target);
}

bool CharacterAbilities::useAbility2(Character & target)
{
	return ability2.get()->use(target);
}
