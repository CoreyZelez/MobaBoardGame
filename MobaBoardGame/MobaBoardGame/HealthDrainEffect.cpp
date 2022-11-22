#include "HealthDrainEffect.h"
#include "HealthEffect.h"
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

		// Handles health absorbtion for absorber.
		const int healthAbsorb = amountPT * absorbRatio;
		HealthEffect healthEff(1, healthAbsorb);
		std::unique_ptr<Effect<CharacterAttributes>> healthEffect = std::make_unique<HealthEffect>(healthEff);
		absorber.addEffect(healthEffect);
	}
	else
	{
		// Handles health absorbtion for absorber.
		const int healthAbsorb = ca.healthAttributes.health * absorbRatio;
		HealthEffect healthEff(1, healthAbsorb);
		std::unique_ptr<Effect<CharacterAttributes>> healthEffect = std::make_unique<HealthEffect>(healthEff);
		absorber.addEffect(healthEffect);

		// Character dies.
		ca.healthAttributes.health = 0;
	}
}
