#include <iostream>
#include "HealthDrainEffect.h"
#include "HealthEffect.h"
#include "Attributes.h"
#include "Character.h"

HealthDrainEffect::HealthDrainEffect(int duration, int amountPT, double absorbRatio, Character &absorber)
	: Effect(duration), amountPT(amountPT), absorbRatio(absorbRatio), absorber(absorber)
{
}

std::unique_ptr<Effect<EntityAttributes>> HealthDrainEffect::clone()
{
	return std::make_unique<HealthDrainEffect>(*this);
}

void HealthDrainEffect::apply(EntityAttributes &ea)
{
	const int health = ea.healthAttributes.health;
	if(health >= amountPT)
	{
		ea.healthAttributes.health -= amountPT;

		// Handles health absorbtion for absorber.
		const int healthAbsorb = amountPT * absorbRatio;
		HealthEffect healthEff(1, healthAbsorb);
		std::unique_ptr<Effect<EntityAttributes>> healthEffect = std::make_unique<HealthEffect>(healthEff);
		absorber.addEffect(healthEffect);
	}
	else
	{
		assert(health > 0);
		// Handles health absorbtion for absorber.
		const int healthAbsorb = ea.healthAttributes.health * absorbRatio;
		HealthEffect healthEff(1, healthAbsorb);
		std::unique_ptr<Effect<EntityAttributes>> healthEffect = std::make_unique<HealthEffect>(healthEff);
		absorber.addEffect(healthEffect);

		// Character dies.
		ea.healthAttributes.health = 0;
	}
}
