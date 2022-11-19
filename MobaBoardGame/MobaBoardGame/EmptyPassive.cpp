#include "EmptyPassive.h"

EmptyPassive::EmptyPassive(Character &character)
	: PassiveAbility(character)
{
}

std::unique_ptr<PassiveAbility> EmptyPassive::clone()
{
	return std::make_unique<EmptyPassive>(*this);
}
