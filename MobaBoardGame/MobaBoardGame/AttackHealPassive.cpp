#include "AttackHealPassive.h"
#include "Character.h"
#include "HealthEffect.h"



AttackHealPassive::AttackHealPassive(int creatureStack, int characterStack, int creatureMultiplier)
	: creatureStack(creatureStack), characterStack(characterStack), creatureMultiplier(creatureMultiplier)
{
}

AttackHealPassive::AttackHealPassive()
	: AttackHealPassive(1, 3, 0.5)
{
}

void AttackHealPassive::update(CharacterAction action)
{
	if(action == postBasicAttackCharacter)
	{
		HealthEffect healthEff(1, stacks);
		std::unique_ptr<Effect<CharacterAttributes>> healthEffect = std::make_unique<HealthEffect>(healthEff);
		getCharacter()->addEffect(healthEffect);
		stacks += characterStack;
	}
	else if(action == postBasicAttackMinion)
	{
		const int healthIncrease = stacks * creatureMultiplier;
		assert(healthIncrease > 0);

		HealthEffect healthEff(1, healthIncrease);
		std::unique_ptr<Effect<CharacterAttributes>> healthEffect = std::make_unique<HealthEffect>(healthEff);
		getCharacter()->addEffect(healthEffect);
		stacks += creatureStack;
	}
	else if(action == death)
	{
		stacks = 0;
	}
}

std::unique_ptr<PassiveAbility> AttackHealPassive::clone()
{
	return std::make_unique<AttackHealPassive>(*this);
}



