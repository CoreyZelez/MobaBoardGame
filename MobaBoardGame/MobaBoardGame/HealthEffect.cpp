#include <memory>
#include <iostream>
#include "HealthEffect.h"
#include "Attributes.h"

struct EntityAttributes;

HealthEffect::HealthEffect(int duration, int amountPT)
	: Effect<EntityAttributes>(duration), amountPT(amountPT)
{
}

std::unique_ptr<Effect<EntityAttributes>> HealthEffect::clone()
{
	return std::make_unique<HealthEffect>(*this);
}

void HealthEffect::apply(EntityAttributes &ea)
{
	ea.healthAttributes.health += amountPT;
}
