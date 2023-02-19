#pragma once
#include "GameEntity.h"
#include <list>
#include <array>
#include <string>
#include "CharacterAbilities.h"
#include "Effect.h"
#include "GameBoard.h"
#include "CharacterAttributesSystem.h"
#include "CharacterStatistics.h"

class Minion;

class Character : public GameEntity
{
	using EntityEffect = Effect<EntityAttributes>;

public:
	Character(GameBoard &gameBoard, std::vector<EntityAttributes>,
		AbilityArsenal abilityArsenal, Team team, sf::Color left, sf::Color right);

	void init();

	void setLastDamaged(Character *character);

	// Getters
	const EntityAttributes &getAttributes() const;  // Return currAttributes reference.
	const EntityAttributes &getBaseAttributes() const;
	int getLevel() const;
	int getAbility1Range() const;
	int getAbility2Range() const;
	bool isAlive() const;
	bool unableToBasicAttack() const;
	bool unableToUseAbility1() const;
	bool unableToUseAbility2() const;

	// Game Actions
	void update();
	bool basicAttack(Character &target);  // True represents successful (i.e in range) attack.
	bool basicAttack(Minion &target);  // True represents successful (i.e in range) attack.
	void addEffect(std::unique_ptr<EntityEffect> effect);
	void addStatusEffect(int duration, Status type);
	bool move(float x, float y);  // Cost determined elsewhere via modified bfs. True indicates move success.
	bool move(Position position);
	void deathReset();  // Called on hp <= 0. Respawns character and resets stats and effects.  
	void spawn();
	int takeDamage(int damage);  // Returns true damage dealt i.e. min(damage, health).

	// Abilities
	bool useAbility1(Character &target);  // Need to create useAbility functions for other object types e.g. creatures.
	bool useAbility2(Character &target);

	// Observer functions
	void subscribeObserver(CharacterObserver *observer);
	void unsubscribeObserver(CharacterObserver *observer);  

	bool hasEffectType(Status type);

	//testing functions.
	void printAttributes();

private:
	// Functions.
	void notifyObservers(CharacterAction action);
	void notifyObservers(CharacterAction action, int quantity);
	void notifyObservers(CharacterAction action, Character &target);
	void notifyObservers(CharacterAction action, Creature *creature);
	void notifyObservers(CharacterAction action, Minion &minion);

	CharacterAttributesSystem attributesSystem;  // Handles effects, items and attributes.
	CharacterStatistics stats;

	// Abilities.
	CharacterAbilities abilities;

	// Observing objects.
	std::list<CharacterObserver*> observers;  // consider rewriting code to use shared pointers.
	Character *lastDamaged = nullptr;  // The last character to damage this character. 

	GameBoard &gameBoard;
};


