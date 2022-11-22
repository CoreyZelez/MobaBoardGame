#pragma once

struct ActionAttributes
{
	// NOTE: can only use 1 ability per turn.
	int points;  // Spent in order to move or attack or use ability.
	int movementPoints;  // Spent in order to move.
	int attackPoints;  // Spent in order to attack.
	int movementCost;  // Typically 1 at start
	int attackCost;  // Typically 2 at start
	double range;  // Basic attack. Uses euclidean distance.
};

struct HealthAttributes
{
	int health;
	int healthRegen;
};

struct CombatAttributes
{
	int physicalDamage;
	int armor;
	int armorPenetration;  // Scaling. In terms of %.
	int lethality;  // Flat armor penetration.
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

