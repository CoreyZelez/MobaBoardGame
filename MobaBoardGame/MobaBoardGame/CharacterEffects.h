#pragma once
#include <list>
#include <memory>
#include "Effect.h"
#include "Attributes.h"

class CharacterEffects
{
	using CharacterEffect = Effect<CharacterAttributes>;

public:
	CharacterEffects();
	void add(const std::unique_ptr<CharacterEffect> &effect);  // Adds effect to effects.
	void update(CharacterAttributes &attributes);  // Calls update on each effect.

private:
	std::list<std::unique_ptr<CharacterEffect>> effects;
};

