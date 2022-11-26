#pragma once
#include <memory>
#include "Effect.h"
#include "Attributes.h"

class HealthEffect : public Effect<EntityAttributes>
{
public:
	HealthEffect(int duration, int amountPT);

	std::unique_ptr<Effect<EntityAttributes>> clone();

	void apply(EntityAttributes &ea);  // Deals health damage.

private:
	int amountPT;  // Amount of damage inflicted.
};

