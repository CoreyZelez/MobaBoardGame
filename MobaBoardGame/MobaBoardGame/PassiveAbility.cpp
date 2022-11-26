#include <assert.h>
#include "Character.h"
#include "PassiveAbility.h"

void PassiveAbility::initCharacter(Character &character)
{
	assert(this->character == nullptr);
	this->character = &character;
	character.subscribeObserver(this);
}

Character* PassiveAbility::getCharacter()
{
	return character;
}
