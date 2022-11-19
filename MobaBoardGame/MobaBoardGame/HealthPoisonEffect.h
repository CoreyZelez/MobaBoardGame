#pragma once
#include <memory>
#include "Effect.h"

struct CharacterAttributes;

class HealthPoisonEffect : public Effect<CharacterAttributes>
{
public:
	HealthPoisonEffect(int duration, int amountPT);

	std::unique_ptr<Effect<CharacterAttributes>> clone();

private:
	void apply(CharacterAttributes &ca);  // Deals health damage.

	int amountPT;  // Amount of damage inflicted.
};

