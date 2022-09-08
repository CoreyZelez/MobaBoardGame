#include "CharacterAttributeEffects.h"
#include <iostream>

CharacterAttributeEffects::CharacterAttributeEffects()
{
	
}

void CharacterAttributeEffects::add(std::unique_ptr<AttributeEffect> &effect)
{
	effects.emplace_back(std::move(effect));
}

void CharacterAttributeEffects::update(CharacterAttributes &attributes)
{
	// Updates each effect and removes effects that have duration 0.
	auto effect = effects.begin();
	while(effects.size() > 0 && effect != effects.cend())
	{
		effect->get()->update(attributes);

		if(effect->get()->isOver())
		{
			effects.erase(effect);
		}
		else
		{
			++effect;
		}
	}
}




