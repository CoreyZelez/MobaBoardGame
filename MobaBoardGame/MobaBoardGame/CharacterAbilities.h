#pragma once
#include <memory>
#include <vector>
#include "Ability.h"
#include "PassiveAbility.h"

struct AbilityArsenal{
	PassiveAbility *passive;
	std::vector<Ability*> abilities;
};

class CharacterAbilities
{
public:
	CharacterAbilities(AbilityArsenal arsenal);

	void initCharacter(Character &character);  // Calls init character on the each ability.
	void update();  // Called at end of every turn.

	// getters
	int getAbilityRange(int abilityNum) const;
	int getAbilityPointCost(int abilityNum) const;
	bool abilityIsOnCooldown(int abilityNum) const;

	bool useAbility(Character &target, int abilityNum);
	bool useAbility(Minion &target, int abilityNum);

private:
	std::unique_ptr<PassiveAbility> passive;
	std::vector<std::unique_ptr<Ability>> abilities;
};

