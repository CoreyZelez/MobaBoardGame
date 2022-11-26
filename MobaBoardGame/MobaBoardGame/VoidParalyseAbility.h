#pragma once
#include "Ability.h"
class VoidParalyseAbility : public Ability
{
public:
	VoidParalyseAbility(std::array<double, 3> levelValues, int duration);

	virtual std::unique_ptr<Ability> clone();

protected:
	bool validTarget(Character &character);
	void applyTarget(Character &target);
	int calculateCooldown() const;

private:
	int duration;
	double absorbRatio;
};

