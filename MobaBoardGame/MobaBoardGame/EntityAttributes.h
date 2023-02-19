#pragma once
#include <array>

class Character;

struct ActionAttributes
{
	// NOTE: can only use 1 ability per turn.
	int points;  // Spent in order to move or attack or use ability.
	int movementPoints;  // Spent in order to move.
	int attackPoints;  // Spent in order to attack.
	int movementCost;  // Typically 1 at start.
	int attackCost;  // Typically 2 at start.
	int range;  // Basic attack. Uses euclidean distance.
};

struct HealthAttributes
{
	int health;
	int healthRegen;
};

struct CombatAttributes
{
	int physicalDamage;
	int armorPenetration;  // In terms of %.
	int lethality;  // Flat armor penetration.
	int armor;
};

struct AbilityAttributes
{
	int abilityPower;
	int abilityPenetration;
	int abilityResist;
};

struct SpecialAttributes
{
	double damageMultiplier = 1;
	double basicAttackDamageMultiplier = 1;
	double abilityDamageMultiplier = 1;
};

struct EntityAttributes
{
	ActionAttributes actionAttributes;
	HealthAttributes healthAttributes;
	CombatAttributes combatAttributes;
	AbilityAttributes abilityAttributes;
	SpecialAttributes specialAttributes;
};


double calculatePhysicalDamageMultiplier(int armor, int armorPenetration, int lethality);

// Need to overload for creatures.
double calculateAbilityMultiplier(const Character &caster, const Character &target);  // Consider passing Attributes instead.



