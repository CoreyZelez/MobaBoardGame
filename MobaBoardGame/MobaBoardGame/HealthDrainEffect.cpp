#include "HealthDrainEffect.h"
#include "Attributes.h"
#include "Character.h"

HealthDrainEffect::HealthDrainEffect(int duration, int amountPT, double absorbRatio, Character &absorber)
	: Effect(duration), amountPT(amountPT), absorbRatio(absorbRatio), absorber(absorber)
{
}

std::unique_ptr<Effect<CharacterAttributes>> HealthDrainEffect::clone()
{
	return std::make_unique<HealthDrainEffect>(*this);
}

void HealthDrainEffect::apply(CharacterAttributes &ca)
{
	if(ca.healthAttributes.health >= amountPT)
	{
		ca.healthAttributes.health -= amountPT;
		absorber.getAttributes().healthAttributes.health += amountPT * absorbRatio;
	}
	else
	{
		absorber.getAttributes().healthAttributes.health += ca.healthAttributes.health * absorbRatio;
		ca.healthAttributes.health = 0;
	}
}
