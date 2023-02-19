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
		effect->get()->update();
		const int postHealth = attributes.healthAttributes.health;
	
		// Pay character gold and xp for damaging effect.
		if(preHealth > postHealth)
		{
			// damage = min(preHealth, preHealth - postHealth)  // determine gold from here
			// Character *sender = effect->get()->getSender();  // outdated 
			// if(sender != nullptr)  // I.E. effect is sent by a character.
			// {
			// 	// CODE HERE TO PAY SENDER.
			// }
		}
	
		minion.handleDeath();  // Removes minion from game if dead.
	
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