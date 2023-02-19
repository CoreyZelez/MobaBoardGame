#pragma once
#include "Ability.h"

/* Target deals reduced damage to ability caster. Heals health of caster.*/
class IntimidationAbility : public Ability
{
public:
	IntimidationAbility();
	IntimidationAbility(std::array<double, 3> damageReductionRatios, std::array<double, 3> healthChangeValues);
	virtual std::unique_ptr<Ability> clone();

protected:
	// Target validation functions.
	bool validTarget(Character &target);

	// Ability effect logic.
	void applyTarget(Character &target);  // Effects on target. Returns boolean on whether target is valid.
	void applySelf();

	virtual int calculateCooldown() const;  // Cooldown after ability use.

private:
	std::array<double, 3> healthChangeValues;
	std::array<double, 3> damageReductionRatios;
};

