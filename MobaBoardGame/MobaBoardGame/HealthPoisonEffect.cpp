#include "HealthPoisonEffect.h"

struct HealthAttributes;

HealthPoisonEffect::HealthPoisonEffect(int amount, int duration)
	: DurationEffect<HealthAttributes>(duration)
{
}

void HealthPoisonEffect::apply(HealthAttributes &ha)
{
	ha.health -= amount;
}
