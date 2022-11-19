#pragma once
#include <memory>
#include "CharacterObserver.h"

enum CharacterAction;

class PassiveAbility : public CharacterObserver
{
public:
	explicit PassiveAbility(Character &character);  
	virtual std::unique_ptr<PassiveAbility> clone() = 0;
	virtual void update(CharacterAction action) {};
	virtual void apply() {};  // Called at start of turn.
	Character &getCharacter();

private:
	Character &character;
};

