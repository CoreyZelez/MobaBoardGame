#pragma once
#include <memory>
#include "Ability.h"
#include "PassiveAbility.h"

struct AbilityArsenal{
	PassiveAbility *passive;
	Ability *ability1;
	Ability *ability2;
};

class CharacterAbilities
{
public:
	CharacterAbilities(AbilityArsenal arsenal);

	void initCharacter(Character &character);  // Calls init character on the each ability.
	void update();  // Called at end of every turn.

	// getters
	int getAbility1Range() const;
	int getAbility2Range() const;
	int getAbility1PointCost() const;
	int getAbility2PointCost() const;
	bool ability1IsOnCooldown() const;
	bool ability2IsOnCooldown() const;

	bool useAbility1(Character &target);
	bool useAbility2(Character &target);

private:
	std::unique_ptr<PassiveAbility> passive;
	std::unique_ptr<Ability> ability1;
	std::unique_ptr<Ability> ability2;

};

