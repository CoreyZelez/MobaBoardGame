#pragma once
#include <array>
#include "Ability.h"

class LifeHarvestAbility : public Ability
{
public:
	LifeHarvestAbility(std::array<double, 3> damageValues);

	virtual std::unique_ptr<Ability> clone();  

protected:
	bool validTarget(Character &character);
	void applyTarget(Character &target);
	int calculateCooldown() const;

private:
	std::array<double, 3> damageValues;
	const int duration = 3;
};

