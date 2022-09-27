#pragma once
#include <List>
#include "Ability.h"

class CharacterTargetAbility : public Ability
{
public:

private:
	std::list<Effect<CharacterEffect>> targetEffects;  // Effects applied to target.

};

