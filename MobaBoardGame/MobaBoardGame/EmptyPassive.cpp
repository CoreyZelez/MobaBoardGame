#include "EmptyPassive.h"

std::unique_ptr<PassiveAbility> EmptyPassive::clone()
{
	return std::make_unique<EmptyPassive>(*this);
}
