#pragma once
#include "DurationEffect.h"
#include "Attributes.h"

class HealthPoisonEffect : public DurationEffect<HealthAttributes>
{
public:
	HealthPoisonEffect(int amount, int duration);

private:
	void apply(HealthAttributes &ha);  // Deals health damage. Non-magic.

	int amount;  // Amount of damage inflicted.
};

