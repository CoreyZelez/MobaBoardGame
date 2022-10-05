#pragma once
#include "CharacterObserver.h"

class PassiveAbility : public CharacterObserver
{
public:
	virtual void update(CharacterAction action, Character &character) = 0;

	virtual void applyPassive(Character &character) = 0;  // Called at start of turn for each ability.
};

