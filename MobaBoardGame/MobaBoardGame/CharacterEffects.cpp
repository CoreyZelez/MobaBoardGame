#include "CharacterEffects.h"
#include <iostream>

CharacterEffects::CharacterEffects()
{
	
}

void CharacterEffects::add(const std::unique_ptr<CharacterEffect> &effect)
{
	effects.emplace_back(effect.get()->clone());
}

void CharacterEffects::update(CharacterAttributes &attributes)
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




