#include "Ability.h"

void Ability::update()
{
	if(cooldown > 0)
	{
		--cooldown;
	}
}

Ability::Ability(const std::list<std::unique_ptr<CharacterEffect>> &selfEffects)
{
	for(const auto& e : selfEffects)
	{
		this->selfEffects.push_back(e->clone());
	}
}
