#include "DurationEffect.h"

void DurationEffect::updateDuration()
{
	--duration;
}

bool DurationEffect::isOver()
{
	return duration == 0;
}
