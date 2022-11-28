#pragma once
#include "Ability.h"
class VoidRendAbility : public Ability
{
public:
	VoidRendAbility(std::array<double, 3> levelValues, int duration);
	VoidRendAbility(std::array<double, 3> levelValues, int duration, double armorMultiplier);
	virtual std::unique_ptr<Ability> clone();  

	// Observer functions.
	virtual void update(TargetCharacterAction action, Character &target);
	virtual void update(TargetCreatureAction action, Creature *target) {};  // To be implemented when add creatures.

protected:
	// Target validation functions.
	virtual bool validTarget(Character &target);

	// Ability effect logic.
	virtual void applyTarget(Character &target);  // Effects on target. Returns boolean on whether target is valid.

	virtual int calculateCooldown() const;  // Cooldown after ability use.

private:
	const int range = 4;
	const double abilityPowerRatio = 1;
	double armorMultiplier = 1;
	double selfMultiplier = 0.5;  // Percent of stats absorbed.
	int duration = 5;  // Suggested duration.

};

