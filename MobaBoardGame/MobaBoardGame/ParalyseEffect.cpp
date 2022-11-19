#include "ParalyseEffect.h"
#include "Attributes.h"

ParalyseEffect::ParalyseEffect(int duration)
	: Effect(duration)
{
}

std::unique_ptr<Effect<CharacterAttributes>> ParalyseEffect::clone()
{
	return std::make_unique<ParalyseEffect>(*this);
}

void ParalyseEffect::apply(CharacterAttributes &ca)
{
	ca.actionAttributes.movementPoints = 0;
	ca.actionAttributes.attackPoints = 0;
}
