#pragma once
#include <Vector>
#include "Effect.h"
#include "Attributes.h"

class Ability
{
public:
	void update();
	Ability();

protected:
	using CharacterEffect = Effect<CharacterAttributes>;

private:
	int cooldown;
	std::vector<Effect<CharacterEffect>> selfEffects;  // Effects applied to self.
};

