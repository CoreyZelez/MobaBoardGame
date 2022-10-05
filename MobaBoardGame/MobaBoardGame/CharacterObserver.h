#pragma once
#include "Character.h"

enum CharacterAction
{
	basicAttackCharacter,
	basicAttackMinion,
};

class CharacterObserver
{
public:
	virtual void update(CharacterAction action, Character& character) {};
};

