#pragma once
#include <array>
#include "Ability.h"

class LifeHarvestAbility : public Ability
{
public:
	LifeHarvestAbility(std::array<int, 3> levelValues, int duration, double absorbRatio);

	virtual std::unique_ptr<Ability> clone();  

protected:
	bool validTarget(Character &character);
	void applyTarget(Character &target) const;
	int calculateCooldown() const;

private:
	int duration;
	double absorbRatio;
};

