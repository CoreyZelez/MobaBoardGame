#pragma once
#include "ActiveEntity.h"
#include <list>
#include <array>
#include <string>
#include "Attributes.h"
#include "CharacterAbilities.h"
#include "EntityEffects.h"
#include "Effect.h"
#include "Item.h"
#include "Position.h"




class Character : public ActiveEntity
{
	using EntityEffect = Effect<EntityAttributes>;

public:
	//Character(std::array<const EntityAttributes, 8> baseAttributes, CharacterAbilities abilities, Team team);
	Character(Position position, std::array<const EntityAttributes, 6> baseAttributes, AbilityArsenal abilityArsenal);

	void init();

	// Getters
	EntityAttributes getAttributes() const;
	EntityAttributes getBaseAttributes() const;
	int getLevel() const;
	int getMovementPoints() const;
	int getActionPoints() const;


	// Game Actions
	void update();
	void basicAttack(Character &target);
	void addEffect(std::unique_ptr<EntityEffect> &effect);
	bool move(Position position, int cost);  // Cost determined elsewhere via modified bfs. True indicates move success.

	// Abilities
	void useAbility1(Character &target);  // Need to create useAbility functions for other object types e.g. creatures.
	void useAbility2(Character &target);

	// Observer functions
	void subscribeObserver(CharacterObserver *observer);
	void unsubscribeObserver(CharacterObserver *observer);  

	bool hasEffectType(EffectType type);

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


