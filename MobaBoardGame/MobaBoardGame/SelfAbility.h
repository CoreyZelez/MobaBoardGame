#pragma once
#include <vector>
#include "Character.h"
#include "Effect.h"
#include "Ability.h"


class SelfAbility : public Ability
{
public:
	SelfAbility(int pointCost, double abilityPowerRatio);
	SelfAbility(int pointCost, std::array<double, 3> abilityPowerRatios);

	virtual std::unique_ptr<Ability> clone() = 0;  // Allows for copying of unique_ptrs to base class.

protected:
	// Target validation functions.
	bool validTarget(Character &target);

	// Ability effect logic.
	virtual void applySelf() {};  // Effects on caster.
	void applyTarget(Character &target) {};  // No effect on target. Use applySelf.
	virtual int calculateCooldown() const = 0;  // Cooldown after ability use.

private:

};







