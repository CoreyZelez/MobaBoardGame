#pragma once
#include "Ability.h"
#include "Character.h"

enum CharacterEvent
{
	attackChampion,
	attackMinion,
	move
};

class PassiveAbility : public Ability
{
public:
	void notify(CharacterEvent event);
	void apply()
private:

};

