#pragma once
#include <list>
#include <memory>
#include "StatusEffect.h"

template<class T> class Effect;

struct EntityAttributes;

class Character;

class StatusEffect;

using EntityEffect = Effect<EntityAttributes>;

class CharacterEffectsManager
{
public:
	CharacterEffectsManager(Character &character);

	void add(const std::unique_ptr<EntityEffect> &effect);  // Adds effect to effects.
	void add(int duration, Status type);  // Adds statusEffect to statusEffects.

	virtual void update();  // Calls update on each effect.
	void clear();

	bool hasEffectType(Status type) const;

protected:
	std::list<std::unique_ptr<EntityEffect>>& getEffects();
	std::list<StatusEffect>& getStatusEffects();

private:
	Character &character;
	std::list<std::unique_ptr<EntityEffect>> effects;
	std::list<StatusEffect> statusEffects;

};

