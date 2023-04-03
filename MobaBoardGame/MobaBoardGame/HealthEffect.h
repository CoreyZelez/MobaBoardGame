#pragma once
#include <memory>
#include "Character.h"
#include "Effect.h"
#include "EntityAttributes.h"

class HealthEffect : public Effect<EntityAttributes>
{
public:
	HealthEffect(int duration, int amountPT, const Character &character);
	HealthEffect(int duration, int amountPT);

	std::unique_ptr<Effect<EntityAttributes>> clone();

	void apply();  // Deals health damage.

private:
	int amountPT;  // Amount of damage inflicted.
	const int *const maxHealth = nullptr;
};

