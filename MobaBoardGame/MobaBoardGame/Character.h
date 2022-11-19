#pragma once
#include <list>
#include <array>
#include "Attributes.h"
#include "CharacterAbilities.h"
#include "CharacterEffects.h"
#include "Effect.h"
#include "Item.h"
#include "Position.h"


enum Team
{
	blue,
	red
};

class Character 
{
	using CharacterEffect = Effect<CharacterAttributes>;

public:
	//Character(std::array<const CharacterAttributes, 8> baseAttributes, CharacterAbilities abilities, Team team);
	Character(Position position, std::array<const CharacterAttributes, 8> baseAttributes, AbilityArsenal abilityArsenal);

	void update();

	CharacterAttributes& getAttributes();

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

	// Core Attributes.
	Team team;
	Position position;
	const std::array<const CharacterAttributes, 8> baseAttributes;  // Position in array specifies level.
	CharacterAttributes currAttributes;  // Recalculated at begginning of each turn from baseAttributes and effects. (Health uniquely is not recalculated).

	// Attribute modifiers.
	CharacterEffects effects;
	std::array<Item, 4> items;

	// Abilities.
	CharacterAbilities abilities;

	// Observing objects.
	// CharacterObserver *observers;

};

