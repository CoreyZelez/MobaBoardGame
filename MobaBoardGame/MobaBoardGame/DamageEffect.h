#pragma once
#include "Effect.h"
#include "Attributes.h"

class DamageEffect : public Effect<CharacterAttributes>
{
public:
	DamageEffect(int duration, int amount);

	std::unique_ptr<Effect<CharacterAttributes>> clone();

	void apply(CharacterAttributes &ca);  // Deals health damage.

private:
	int amount;  // Damage stat increase.
};

