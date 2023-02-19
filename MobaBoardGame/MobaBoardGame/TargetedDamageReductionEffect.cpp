#include "TargetedDamageReductionEffect.h"
#include "Character.h"

TargetedDamageReductionEffect::TargetedDamageReductionEffect(int duration, double damageReductionRatio, Character &sender, Character &receiver)
	: Effect<EntityAttributes>(duration, sender, receiver), damageReductionRatio(damageReductionRatio)
{
	receiver.subscribeObserver(this);  // Observes receivers attacks. Applys damage reduction when attacking sender
}

TargetedDamageReductionEffect::~TargetedDamageReductionEffect()
{
	getReceiver()->unsubscribeObserver(this);
	std::cout << "fuck yes it works!" << std::endl;
}

std::unique_ptr<Effect<EntityAttributes>> TargetedDamageReductionEffect::clone()
{
	return std::make_unique<TargetedDamageReductionEffect>(*this);
}

void TargetedDamageReductionEffect::update(CharacterAction action, Character &character)
{
	if(&character != getSender())
	{
		return;
	}

	EntityAttributes &ea = getT();

	double ratio = 1 - damageReductionRatio;

	if(action == preBasicAttackDamageCalculation || action == preAbilityDamageCalculation)
	{
		ea.specialAttributes.damageMultiplier *= ratio;
	}
	else if(action == postBasicAttackDamageDealt || postAbilityDamageDealt)
	{
		ea.specialAttributes.damageMultiplier /= ratio;  // Reverses changes.
	}
}


