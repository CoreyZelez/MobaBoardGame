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

private:
	std::unique_ptr<PassiveAbility> passive;
	std::unique_ptr<Ability> ability1;
	std::unique_ptr<Ability> ability2;
};

