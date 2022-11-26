#include "EntityEffects.h"
#include "Effect.h"
#include <iostream>

EntityEffects::EntityEffects()
{
	
}

void EntityEffects::add(const std::unique_ptr<EntityEffect> &effect)
{
	effects.emplace_back(effect.get()->clone());
}

void EntityEffects::update(EntityAttributes &attributes)
{
	// Updates each effect and removes effects that have duration 0.
	auto effect = effects.begin();
	while(effect != effects.cend())
	{
		effect->get()->update(attributes);

		if(effect->get()->isOver())
		{
			effects.erase(effect++);
		}
		else
		{
			++effect;
		}
	}
}




