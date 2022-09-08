#pragma once
#include <list>
#include <array>
#include "CharacterAttributeEffects.h"
#include "Effect.h"
#include "Attributes.h"
#include "Item.h"


class Character
{
	using AttributeEffect = Effect<CharacterAttributes>;

public:
	Character(std::array<const CharacterAttributes, 8> baseAttributes);

	void update();

	void basicAttack(Character &enemyCharacter);

	//testing functions.
	void printAttributes();
	//end testing functions.

	// PUBLIC FOR TESTING
	void addEffect(std::unique_ptr<AttributeEffect> &effect);

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
	CharacterAttributeEffects attributeEffects;
	std::array<Item, 4> items;


};

