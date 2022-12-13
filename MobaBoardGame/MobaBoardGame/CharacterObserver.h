#pragma once
#include "Action.h"

class Character;
class Creature;

class CharacterObserver
{
public:
	virtual void update(CharacterAction action) = 0;
	virtual void update(TargetCharacterAction action, Character &target) = 0;  
	virtual void update(TargetCreatureAction action, Creature *target) = 0;

};

