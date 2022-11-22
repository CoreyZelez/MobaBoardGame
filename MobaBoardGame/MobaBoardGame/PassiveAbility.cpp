#include <assert.h>
#include "Character.h"
#include "PassiveAbility.h"

void PassiveAbility::initCharacter(Character &character)
{
	assert(this->character == nullptr);
	this->character = &character;
}

Character* PassiveAbility::getCharacter()
{
	return character;
}
