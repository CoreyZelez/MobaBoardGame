#pragma once
#include "Ability.h"

class CharacterTargetAbility : public Ability
{
public:

private:
	std::vector<Effect<CharacterEffect>> targetEffects;  // Effects applied to target.

};

