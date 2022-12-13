#pragma once
#include <memory>
#include "Effect.h"
#include "EntityAttributes.h"

class HealthEffect : public Effect<EntityAttributes>
{
public:
	HealthEffect(int duration, int amountPT, int maxHealth);

	std::unique_ptr<Effect<EntityAttributes>> clone();

	void apply(EntityAttributes &ea);  // Deals health damage.

private:
	int amountPT;  // Amount of damage inflicted.
	const int maxHealth;
};

