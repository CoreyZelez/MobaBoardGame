#include <iostream>
#include "HealthDrainEffect.h"
#include "HealthEffect.h"
#include "EntityAttributes.h"
#include "Character.h"

HealthDrainEffect::HealthDrainEffect(int duration, int amountPT, double absorbRatio, Character &sender)
	: Effect(duration, sender), amountPT(amountPT), absorbRatio(absorbRatio)
{

}

std::unique_ptr<Effect<EntityAttributes>> HealthDrainEffect::clone()
{
	return std::make_unique<HealthDrainEffect>(*this);
}

void HealthDrainEffect::apply()
{
	EntityAttributes &ea = getT();
	const int health = ea.healthAttributes.health;

	if(health >= amountPT)
	{
		ea.healthAttributes.health -= amountPT;

		// Handles health absorbtion for absorber.
		const int healthAbsorb = amountPT * absorbRatio;
		std::unique_ptr<Effect<EntityAttributes>> healthEffect = std::make_unique<HealthEffect>(1, healthAbsorb, *getSender());
		getSender()->addEffect(std::move(healthEffect));
	}
	else
	{
		assert(health > 0);
		// Handles health absorbtion for absorber.
		const int healthAbsorb = ea.healthAttributes.health * absorbRatio;
		std::unique_ptr<Effect<EntityAttributes>> healthEffect = std::make_unique<HealthEffect>(1, healthAbsorb, *getSender());
		getSender()->addEffect(std::move(healthEffect));

		// Character dies.
		ea.healthAttributes.health = 0;
	}
}
