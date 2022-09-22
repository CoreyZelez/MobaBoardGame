#include "Ability.h"

void Ability::update()
{
	if(cooldown > 0)
	{
		--cooldown;
	}
}
