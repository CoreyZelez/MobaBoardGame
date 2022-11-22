#pragma once
#include "PassiveAbility.h"

class EnhancedBasicPassive : public PassiveAbility
{
public:
	EnhancedBasicPassive(double damageMultiplier, int stackTrigger, int duration);

	void update(CharacterAction action);

private:
	double damageMultiplier; 
	int stackTrigger;  // Num stacks to get enhanced attack.
	int duration;  // How many turns the enhanced attack can be held.
	int attackCnt = 0;
	int stacks = 0;  // Basic attacks grant stacks.
	int attackIncrease = 0;  // Increase of damage on enhanced attack.
};

