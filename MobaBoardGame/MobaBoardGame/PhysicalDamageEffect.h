#pragma once
#include "Effect.h"
#include "EntityAttributes.h"

class PhysicalDamageEffect : public Effect<EntityAttributes>
{
public:
	PhysicalDamageEffect(int duration, int amount);

	std::unique_ptr<Effect<EntityAttributes>> clone();

	void apply();  // Deals health damage.

private:
	int amount;  // Damage stat increase.
};

