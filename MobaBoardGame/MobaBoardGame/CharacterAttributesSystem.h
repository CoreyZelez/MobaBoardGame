#pragma once
#include <array>
#include "AttributesSystem.h"
#include "CharacterEffectsManager.h"
#include "EntityAttributes.h"
#include "Item.h"

class Character;

class CharacterAttributesSystem : public AttributesSystem<Character>
{
	using EntityEffect = Effect<EntityAttributes>;

public:
	CharacterAttributesSystem(Character &character, const std::vector<EntityAttributes> coreBaseAttributes);

	void levelUp();

private:

	std::array<Item, 4> items;  // Items should affect baseAttributes.

	// const static std::array<int, 6> experienceForLevel;
	// int experience = 0;
};

