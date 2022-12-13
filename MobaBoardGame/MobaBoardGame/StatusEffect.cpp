#include "StatusEffect.h"

StatusEffect::StatusEffect(int duration, Status type)
	: duration(duration), type(type)
{
}

void StatusEffect::updateDuration()
{
	--duration;
}

bool StatusEffect::isOver()
{
	assert(duration >= 0);
	return duration == 0;
}
