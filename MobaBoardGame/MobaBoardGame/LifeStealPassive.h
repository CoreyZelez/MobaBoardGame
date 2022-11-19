#pragma once
#include <memory>
#include "PassiveAbility.h"

enum CharacterAction;

class LifeStealPassive : public PassiveAbility
{
public:
	virtual void update(CharacterAction action);

	std::unique_ptr<PassiveAbility> clone();

protected:
	void incrementStacks(int amount);

private:
	int stacks = 0;
};

