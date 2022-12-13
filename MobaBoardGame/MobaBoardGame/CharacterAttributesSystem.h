#pragma once
#include <array>
#include "CharacterEffectsManager.h"
#include "EntityAttributes.h"
#include "Item.h"

class Character;

class CharacterAttributesSystem
{
public:
	using EntityEffect = Effect<EntityAttributes>;

public:
	CharacterAttributesSystem(Character &character, std::array<const EntityAttributes, 6> baseAttributes);

	EntityAttributes& getAttributes();
	EntityAttributes getAttributes() const;
	EntityAttributes getBaseAttributes() const;
	int getLevel() const;

	void update();

	bool isAlive() const;
	bool hasEffectType(Status type) const;

	void addEffect(std::unique_ptr<EntityEffect> &effect);
	void addStatusEffect(int duration, Status type);
	void reset();

private:
	void resetCurrAttributes();

	Character &character;

	const std::array<const EntityAttributes, 6> baseAttributes;  // Position in array specifies level.
	EntityAttributes currAttributes;  // Recalculated at begginning of each turn from baseAttributes and effects. (Health uniquely is not recalculated).

	CharacterEffectsManager effects;

	std::array<Item, 4> items;

	// Level information.
	const static std::array<int, 6> experienceForLevel;
	int experience = 0;
	int level = 1;
};

