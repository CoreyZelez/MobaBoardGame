#pragma once
#include <memory>
#include "Effect.h"
#include "Attributes.h"

class HealthPoisonEffect : public Effect<CharacterAttributes>
{
public:
	HealthPoisonEffect(int duration, int amount);

	std::unique_ptr<Effect<CharacterAttributes>> clone();

private:
	void apply(CharacterAttributes &ca);  // Deals health damage.

	int amount;  // Amount of damage inflicted.
};

