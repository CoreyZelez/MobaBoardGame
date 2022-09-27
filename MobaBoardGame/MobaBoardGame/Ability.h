#pragma once
#include <List>
#include <memory>
#include "Effect.h"
#include "Attributes.h"

class Ability
{
protected:
	using CharacterEffect = Effect<CharacterAttributes>;

public:
	Ability(const std::list<std::unique_ptr<CharacterEffect>> &selfEffects);
	void update();

private:
	int cooldown;
	std::list<std::unique_ptr<CharacterEffect>> selfEffects;  // Effects applied to self.
};

