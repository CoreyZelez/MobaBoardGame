#pragma once
#include "PassiveAbility.h"
class EmptyPassive : public PassiveAbility
{
public:
	EmptyPassive(Character &character);

	virtual std::unique_ptr<PassiveAbility> clone();

private:

};

