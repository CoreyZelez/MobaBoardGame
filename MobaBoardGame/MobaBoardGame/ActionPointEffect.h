#pragma once
#include "Effect.h"

struct EntityAttributes;

class ActionPointEffect : public Effect<EntityAttributes>
{
public:
	ActionPointEffect(int duration, int amount);

	std::unique_ptr<Effect<EntityAttributes>> clone();

	void apply();  // Deals health damage.

private:
	int amount;  // Damage stat increase.
};

