#pragma once
#include <list>
#include <memory>

template<class T> class Effect;
struct EntityAttributes;

class EntityEffects
{
	using EntityEffect = Effect<EntityAttributes>;

public:
	EntityEffects();
	void add(const std::unique_ptr<EntityEffect> &effect);  // Adds effect to effects.
	void update(EntityAttributes &attributes);  // Calls update on each effect.

private:
	std::list<std::unique_ptr<EntityEffect>> effects;
};

