#pragma once
#include "CharacterAction.h"

class Character;

class CharacterObserver
{
public:
	virtual void update(CharacterAction action) = 0;
};

