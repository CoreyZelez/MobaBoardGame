#include <memory>
#include "Ability.h"
#include "PassiveAbility.h"
#include "EmptyPassive.h"


Ability::Ability(Character &character)
	: passive(std::make_unique<EmptyPassive>(character))
{
}

Ability::Ability(PassiveAbility *passive)
	: passive(passive->clone())
{
}

bool Ability::use(Character &target)
{
	if(validTarget(target))
	{
		Character &owner = passive.get()->getCharacter();
		applyTarget(owner, target);
		applySelf(owner);
		cooldown = calculateCooldown(owner);
		return true;
	}

	return false;
}

void Ability::applyPassive()
{
	passive.get()->apply();
}

const Character* Ability::getOwner()
{
	return &passive.get()->getCharacter();
}




