#pragma once
#include <memory>
#include "Effect.h"
#include "Attributes.h"

class HealthEffect : public Effect<CharacterAttributes>
{
public:
	HealthEffect(int duration, int amountPT);

	std::unique_ptr<Effect<CharacterAttributes>> clone();

	void apply(CharacterAttributes &ca);  // Deals health damage.

private:
	int amountPT;  // Amount of damage inflicted.
};

