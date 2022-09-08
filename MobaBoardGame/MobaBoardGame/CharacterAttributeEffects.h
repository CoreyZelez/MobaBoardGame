#pragma once
#include <List>
#include <memory>
#include "Effect.h"
#include "Attributes.h"

class CharacterAttributeEffects
{
	using AttributeEffect = Effect<CharacterAttributes>;

public:
	CharacterAttributeEffects();
	void add(std::unique_ptr<AttributeEffect> &effect);
	void update(CharacterAttributes &attributes);  // Calls update on each effect.

private:
	std::list<std::unique_ptr<AttributeEffect>> effects;
};

