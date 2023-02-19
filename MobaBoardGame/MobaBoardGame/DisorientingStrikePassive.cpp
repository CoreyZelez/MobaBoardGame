#include "DisorientingStrikePassive.h"
#include "ActionPointEffect.h"
#include "MovementPointEffect.h"

const double criticalHealthRatio = 0.5;

std::unique_ptr<PassiveAbility> DisorientingStrikePassive::clone()
{
	return std::make_unique<DisorientingStrikePassive>(*this);
}

void DisorientingStrikePassive::update(CharacterAction action, Character &target)
{
	if(action == preBasicAttackDamageCalculation)
	{
		const int health = target.getAttributes().healthAttributes.health;
		const int baseHealth = target.getBaseAttributes().healthAttributes.health;
		const double healthRatio = (double)health / (double)baseHealth;
		if(healthRatio < criticalHealthRatio)
		{
			std::unique_ptr<Effect<EntityAttributes>> effect1 = std::make_unique<ActionPointEffect>(2, -1);
			std::unique_ptr<Effect<EntityAttributes>> effect2 = std::make_unique<MovementPointEffect>(2, -2);
			target.addEffect(std::move(effect1));
			target.addEffect(std::move(effect2));
		}
		else
		{
			std::unique_ptr<Effect<EntityAttributes>> effect1 = std::make_unique<ActionPointEffect>(2, -1);
			std::unique_ptr<Effect<EntityAttributes>> effect2 = std::make_unique<MovementPointEffect>(2, -1);
			target.addEffect(std::move(effect1));
			target.addEffect(std::move(effect2));
		}
	}
}
