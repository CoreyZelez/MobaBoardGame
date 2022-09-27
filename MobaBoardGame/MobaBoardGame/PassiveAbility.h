#pragma once
#include <List>
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
	PassiveAbility(std::list<std::unique_ptr<CharacterEffect>> selfEffects);

	virtual void notify(CharacterEvent event);
	virtual void apply();
private:

};

