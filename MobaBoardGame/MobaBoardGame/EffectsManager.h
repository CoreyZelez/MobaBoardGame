#pragma once
#include <list>
#include <memory>
#include "StatusEffect.h"

/* In future allow for any effect type by 
   adding Q to template then Effect<Q>.
*/

template<class T> class Effect;
struct EntityAttributes;
using EntityEffect = Effect<EntityAttributes>;

template<class T>
class EffectsManager
{
public:

	EffectsManager(T &t): t(t) {};

	T &getSubject()
	{
		return t;
	}

	void add(const std::unique_ptr<EntityEffect> &effect)  // Adds effect to effects.
	{
		effects.emplace_back(effect.get()->clone());
	}

	void add(int duration, Status type)  // Adds statusEffect to statusEffects.
	{
		statusEffects.push_back(StatusEffect(duration, type));
	}

	virtual void update() = 0;  // Calls update on each effect.

	void clear()
	{
		effects.clear();
	}

	bool hasEffectType(Status type) const
	{
		for(const auto &statusEffect : statusEffects)
		{
			if(statusEffect.getType() == type)
			{
				return true;
			}
		}

		return false;
	}

protected:

	std::list<std::unique_ptr<EntityEffect>>& getEffects()
	{
		return effects;
	}

	std::list<StatusEffect>& getStatusEffects()
	{
		return statusEffects;
	}

private:
	T &t;
	std::list<std::unique_ptr<EntityEffect>> effects;
	std::list<StatusEffect> statusEffects;

};

