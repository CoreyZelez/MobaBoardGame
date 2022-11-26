#pragma once
#include <list>
#include <array>
#include <string>
#include "Attributes.h"
#include "CharacterAbilities.h"
#include "EntityEffects.h"
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
	using EntityEffect = Effect<EntityAttributes>;

public:
	//Character(std::array<const EntityAttributes, 8> baseAttributes, CharacterAbilities abilities, Team team);
	Character(Position position, std::array<const EntityAttributes, 6> baseAttributes, AbilityArsenal abilityArsenal);

	void init();
	void initName(std::string name);

	// Getters
	EntityAttributes getAttributes() const;
	EntityAttributes getBaseAttributes() const;
	int getLevel() const;

	// Game Actions
	void update();
	void basicAttack(Character &target);
	void addEffect(std::unique_ptr<EntityEffect> &effect);
	// Abilities
	void useAbility1(Character &target);  // Need to create useAbility functions for other object types e.g. creatures.
	void useAbility2(Character &target);

	// Observer functions
	void subscribeObserver(CharacterObserver *observer);
	void unsubscribeObserver(CharacterObserver *observer);  

	//testing functions.
	void printAttributes();

private:
	// Functions.
	void updateCurrAttributes();  
	void notifyObservers(CharacterAction action);
	void notifyObservers(TargetCharacterAction action, Character &target);
	void notifyObservers(TargetCreatureAction action, Creature *creature);

	void takeDamage(int damage);

	// Level information.
	const static std::array<int, 6> experienceForLevel; 
	CharacterLevelInformation levelInformation;  // Curr level and xp.

	// Core Attributes.
	std::string name;
	Team team;
	Position position;
	const std::array<const EntityAttributes, 6> baseAttributes;  // Position in array specifies level.
	EntityAttributes currAttributes;  // Recalculated at begginning of each turn from baseAttributes and effects. (Health uniquely is not recalculated).

	// Attribute modifiers.
	EntityEffects effects;
	std::array<Item, 4> items;

	// Abilities.
	CharacterAbilities abilities;

	// Observing objects.
	std::list<CharacterObserver*> observers;  // consider rewriting code to use shared pointers.
};


