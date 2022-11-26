#include "CharacterAbilities.h"

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
}

void CharacterAbilities::useAbility1(Character & target)
{
	ability1.get()->use(target);
}

void CharacterAbilities::useAbility2(Character & target)
{
	ability2.get()->use(target);
}
