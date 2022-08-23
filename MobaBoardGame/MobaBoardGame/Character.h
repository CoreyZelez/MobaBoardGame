#pragma once
#include <list>
#include <array>
#include "CharacterDurationEffects.h"
#include "DurationEffect.h"
#include "Attributes.h"
#include "Item.h"


class Character
{
public:
	Character(std::array<const CharacterAttributes, 8> baseAttributes);

	void update();

	void basicAttack(Character &enemyCharacter);

	//testing functions.
	void printAttributes();
	//end testing functions.

private:
	// Functions.
	void updateCurrAttributes();  // Recalled on self affecting abilities. Doesn't affect ability durations.

	// Level information.
	const static std::array<int, 8> experienceForLevel; //
	LevelInformation levelInformation;  // Curr level and xp.

	// Attributes.
	const std::array<const CharacterAttributes, 8> baseAttributes;  // Position in array specifies level.
	CharacterAttributes currAttributes;  // Recalculated at begginning of each turn from baseAttributes and effects. (Health uniquely is not recalculated).

	// Attribute modifiers.
	CharacterDurationEffects durationEffects;
	std::array<Item, 4> items;


};

