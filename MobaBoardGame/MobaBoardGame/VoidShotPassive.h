#pragma once
#include <array>
#include "PassiveAbility.h"

/* Causes basic attack to deal true damage over time whilst also slowing the target (after stacks reached).
Damage bonus to a void shot on a voidInfliction target. */
class VoidShotPassive : public PassiveAbility
{
public:
	VoidShotPassive(std::array<int, 6> trueDamage, int stackTrigger, int duration);

	std::unique_ptr<PassiveAbility> clone();

	void update(TargetCharacterAction action, Character &target);
	void update(TargetCreatureAction action, Creature *target);

private:
	int stackTrigger;  // Num stacks to get enhanced attack.
	int duration;  // How many turns the enhanced attack can be held.
	int stacks = 0;  // Basic attacks grant stacks.
	std::array<int, 6> trueDamage;  // Total true damage applied over duration for a given character level.
};


