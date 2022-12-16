#include "MinionEffectsManager.h"
#include "Minion.h"

MinionEffectsManager::MinionEffectsManager(Minion & minion)
	: EffectsManager<Minion>(minion)
{}

void MinionEffectsManager::update()
{
	using EntityEffect = Effect<EntityAttributes>;

	Minion &minion = getSubject();

	std::list<std::unique_ptr<EntityEffect>>& effects = getEffects();
	std::list<StatusEffect>& statusEffects = getStatusEffects();

	EntityAttributes &attributes = minion.getAttributes();

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
				minion.setLastDamaged(sender);
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