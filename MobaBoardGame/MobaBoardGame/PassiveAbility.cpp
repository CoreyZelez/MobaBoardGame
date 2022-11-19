#include "PassiveAbility.h"

PassiveAbility::PassiveAbility(Character &character)
	: character(character)
{
}

Character& PassiveAbility::getCharacter()
{
	return character;
}
