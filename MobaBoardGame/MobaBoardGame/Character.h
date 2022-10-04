#pragma once
#include <list>
#include <array>
#include "CharacterEffects.h"
#include "Effect.h"
#include "Attributes.h"
#include "Item.h"
#include "CharacterAbilities.h"
#include "Position.h"


class Character : public Position
{
	using CharacterEffect = Effect<CharacterAttributes>;

public:
	//Character(std::array<const CharacterAttributes, 8> baseAttributes, CharacterAbilities abilities);
	Character(std::array<const CharacterAttributes, 8> baseAttributes);

	void update();

	void basicAttack(Character &enemyCharacter);

	//testing functions.
	void printAttributes();
	//end testing functions.

	void addEffect(std::unique_ptr<CharacterEffect> &effect);

private:
	// Functions.
	void updateCurrAttributes();  // Recalled on self affecting abilities. Doesn't affect ability durations.

	// Level information.
	const static std::array<int, 8> experienceForLevel; 
	LevelInformation levelInformation;  // Curr level and xp.

	// Attributes.
	const std::array<const CharacterAttributes, 8> baseAttributes;  // Position in array specifies level.
	CharacterAttributes currAttributes;  // Recalculated at begginning of each turn from baseAttributes and effects. (Health uniquely is not recalculated).

	// Attribute modifiers.
	CharacterEffects effects;
	std::array<Item, 4> items;

	// Abilities.
	CharacterAbilities abilities;

};

