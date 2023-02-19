#pragma once
#include "Action.h"

class Character;
class Creature;
class Minion;

class CharacterObserver
{
public:
	virtual void update(CharacterAction action) {};
	virtual void update(CharacterAction action, int quantity) {};
	virtual void update(CharacterAction action, Character &character) {};
	virtual void update(CharacterAction action, Creature *creature) {};
	virtual void update(CharacterAction action, Minion &minion) {};
};

