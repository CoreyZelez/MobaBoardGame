#include <memory>
#include <iostream>
#include "HealthEffect.h"
#include "EntityAttributes.h"

struct EntityAttributes;

HealthEffect::HealthEffect(int duration, int amountPT, const Character &character)
	: Effect<EntityAttributes>(duration), amountPT(amountPT), maxHealth(character.getBaseAttributes().healthAttributes.health)
{
}

std::unique_ptr<Effect<EntityAttributes>> HealthEffect::clone()
{
	return std::make_unique<HealthEffect>(*this);
}

void HealthEffect::apply()
{
	EntityAttributes &ea = getT();
	ea.healthAttributes.health += amountPT;
	if(ea.healthAttributes.health > maxHealth)
	{
		ea.healthAttributes.health = maxHealth;
	}
}
