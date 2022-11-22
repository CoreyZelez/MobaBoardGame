#pragma once
#include "PassiveAbility.h"
class EmptyPassive : public PassiveAbility
{
public:
	virtual std::unique_ptr<PassiveAbility> clone();

private:

};

