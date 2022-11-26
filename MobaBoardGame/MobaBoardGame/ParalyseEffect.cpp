#include "ParalyseEffect.h"
#include "Attributes.h"

ParalyseEffect::ParalyseEffect(int duration)
	: Effect(duration)
{
}

std::unique_ptr<Effect<EntityAttributes>> ParalyseEffect::clone()
{
	return std::make_unique<ParalyseEffect>(*this);
}

void ParalyseEffect::apply(EntityAttributes &ea)
{
	ea.actionAttributes.movementPoints = 0;
	ea.actionAttributes.attackPoints = 0;
}
