#pragma once
#include <memory>
#include "CharacterObserver.h"

enum CharacterAction;

class PassiveAbility : public CharacterObserver
{
public:
	virtual std::unique_ptr<PassiveAbility> clone() = 0;

	// Observer functions.
	virtual void update(CharacterAction action) {};
	virtual void update(TargetCharacterAction action, Character &target) {};  // Use when you need to add 
	virtual void update(TargetCreatureAction action, Creature *target) {};

	virtual void apply() {};  // Called at start of turn.
	void initCharacter(Character &character);  // Called (once) after ability added to character.
	Character *getCharacter();

private:
	Character *character = nullptr;  // Should never be changed once set by initCharacter.
};

