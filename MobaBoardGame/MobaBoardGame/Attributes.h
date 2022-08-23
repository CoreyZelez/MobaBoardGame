#pragma once

struct ActionAttributes
{
	// NOTE: can only use 1 ability per turn.
	int points;  // Spent in order to move or attack or use ability.
	int movementPoints;  // Spent in order to move.
	int attackPoints;  // Spent in order to attack.
	int movementCost = 1;
	int attackCost = 2;
};

struct HealthAttributes
{
	int health;
	int healthRegen;
};

struct CombatAttributes
{
	int damage;
	int armour;
	int armourPenetration;
};

struct AbilityAttributes
{
	int abilityPower;
	int abilityPenetration;
	int abilityResist;
};

struct LevelInformation
{
	int level = 0;
	int experience = 0;
};

struct CharacterAttributes
{
	ActionAttributes actionAttributes;
	HealthAttributes healthAttributes;
	CombatAttributes combatAttributes;
	AbilityAttributes abilityAttributes;
};

