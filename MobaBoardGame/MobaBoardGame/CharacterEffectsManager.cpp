#include "CharacterEffectsManager.h"
#include "Effect.h"
#include "StatusEffect.h"
#include "Character.h"
#include <iostream>

CharacterEffectsManager::CharacterEffectsManager(Character &character)
	: EffectsManager<Character>(character)
{}

void CharacterEffectsManager::update()
{
	using EntityEffect = Effect<EntityAttributes>; 

	Character &character = getSubject();

	std::list<std::unique_ptr<EntityEffect>>& effects = getEffects();
	std::list<StatusEffect>& statusEffects = getStatusEffects();

	EntityAttributes &attributes = character.getAttributes();

	// Updates each effect and removes effects that have duration 0.
	auto effect = effects.begin();
	while(effect != effects.end())
	{
		const int preHealth = attributes.healthAttributes.health;
		effect->get()->update(attributes);
		const int postHealth = attributes.healthAttributes.health;

		if(preHealth > postHealth)
		{
			Character *sender = effect->get()->getSender();
			if(sender != nullptr)  // I.E. effect is sent by a character.
			{
				character.setLastDamaged(sender);
			}
		}

		// Handles character death.
		if(!character.isAlive())
		{
			assert(preHealth > postHealth);
			character.deathReset();
			return;
		}


		if(effect->get()->isOver())
		{
			effects.erase(effect++);
		}
		else
		{
			++effect;
		}
	}

	// Updates statusEffects.
	auto statusEffect = statusEffects.begin();
	while(statusEffect != statusEffects.end())
	{
		statusEffect->updateDuration();

		if(statusEffect->isOver())
		{
			statusEffects.erase(statusEffect++);
		}
		else
		{
			++statusEffect;
		}
	}
}
