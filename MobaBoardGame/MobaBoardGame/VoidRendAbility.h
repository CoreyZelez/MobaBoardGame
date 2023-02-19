#pragma once
#include "Ability.h"

/* Absorbs Armor and physical damage stats from target. Applys void infliction.*/
class VoidRendAbility : public Ability
{
public:
	VoidRendAbility(std::array<double, 3> statChangeValues);
	virtual std::unique_ptr<Ability> clone();  

	// Observer functions.
	virtual void update(CharacterAction action, Character &target);
	virtual void update(CharacterAction action, Creature *target) {};  // To be implemented when add creatures. MAYBE NOT FOR THIS ABILITY.

protected:
	// Target validation functions.
	virtual bool validTarget(Character &target);

	// Ability effect logic.
	virtual void applyTarget(Character &target);  // Effects on target. Returns boolean on whether target is valid.

	virtual int calculateCooldown() const;  // Cooldown after ability use.

private:
	std::array<double, 3> statChangeValues;
	const double armorMultiplier = 1;
	const double selfMultiplier = 0.5;  // Percent of stats absorbed.
	const int duration = 5;  // Suggested duration.
};

