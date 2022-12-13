#pragma once
#include "Ability.h"

/* Paralyses enemy. Gives them void infliction.*/
class VoidParalyseAbility : public Ability
{
public:
	VoidParalyseAbility(std::array<double, 3> damageValues);

	virtual std::unique_ptr<Ability> clone();

protected:
	bool validTarget(Character &character);
	void applyTarget(Character &target);
	void applySelf();
	int calculateCooldown() const;

private:
	std::array<double, 3> damageValues;  // Base damage for each level.
	const int duration = 4;  // Paralyse duration.
};

