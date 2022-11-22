#include "LifeHarvestAbility.h"
#include "HealthDrainEffect.h"

LifeHarvestAbility::LifeHarvestAbility(std::array<int, 3> levelValues, int duration, double absorbRatio)
	: Ability(levelValues, 3), duration(duration), absorbRatio(absorbRatio)
{
}

std::unique_ptr<Ability> LifeHarvestAbility::clone()
{
	return std::make_unique<LifeHarvestAbility>(getLevelValues(), duration, absorbRatio);
}

bool LifeHarvestAbility::validTarget(Character &character)
{
	return &character != getOwner();
}

void LifeHarvestAbility::applyTarget(Character &target) const
{
	HealthDrainEffect hde();
}

int LifeHarvestAbility::calculateCooldown() const
{
	return 3;
}
