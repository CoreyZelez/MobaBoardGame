#pragma once
#include "SelfAbility.h"

/* Greatly increases Armor and magic resist at the cost of movement.*/
class ResistantSentinelAbility : public SelfAbility
{
public:
	ResistantSentinelAbility(std::array<double, 3> armorIncreases, std::array<double, 3> magicResistIncreases);

	std::unique_ptr<Ability> clone();

protected:
	void applySelf();
	int calculateCooldown() const;

private:
	std::array<double, 3> armorIncreases;
	std::array<double, 3> magicResistIncreases;

};
