#pragma once
#include <array>


struct ActionAttributes
{
	// NOTE: can only use 1 ability per turn.
	int points;  // Spent in order to move or attack or use ability.
	int movementPoints;  // Spent in order to move.
	int attackPoints;  // Spent in order to attack.
	int movementCost;  // Typically 1 at start.
	int attackCost;  // Typically 2 at start.
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

struct CharacterLevelInformation
{
	int level = 1;
	int experience = 0;
	const static std::array<int, 6> experienceForLevel; 
};

struct EntityAttributes
{
	ActionAttributes actionAttributes;
	HealthAttributes healthAttributes;
	CombatAttributes combatAttributes;
	AbilityAttributes abilityAttributes;
};

double calculatePhysicalDamageMultiplier(int armor, int armorPenetration, int lethality);

class Character;
// Need to overload for creatures.
double calculateAbilityMultiplier(const Character &caster, const Character &target);
