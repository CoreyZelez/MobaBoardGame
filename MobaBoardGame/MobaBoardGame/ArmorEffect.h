#pragma once
#include "Effect.h"
#include "EntityAttributes.h"
class ArmorEffect : public Effect<EntityAttributes>
{
public:
	ArmorEffect(int duration, int amount);

	std::unique_ptr<Effect<EntityAttributes>> clone();

	void apply(EntityAttributes &ea);  // Deals health damage.

private:
	int amount;  // Damage stat increase.
};

