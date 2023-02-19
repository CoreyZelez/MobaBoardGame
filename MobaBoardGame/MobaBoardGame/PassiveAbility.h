#pragma once
#include <memory>
#include "CharacterObserver.h"

enum CharacterAction;

class PassiveAbility : public CharacterObserver
{
public:
	virtual std::unique_ptr<PassiveAbility> clone() = 0;

	virtual void apply() {};  // Called at start of turn.
	void initCharacter(Character &character);  // Called (once) after ability added to character.
	Character *getCharacter();

private:
	Character *character = nullptr;  // Should never be changed once set by initCharacter.
};

