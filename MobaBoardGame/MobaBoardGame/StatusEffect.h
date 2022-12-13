#pragma once
#include "Effect.h"


enum Status
{
	voidInfliction
};


class StatusEffect
{
public:
	StatusEffect(int duration, Status type);

	virtual Status getType() const { return type; }

	void updateDuration();
	bool isOver();


private:
	Status type;
	int duration;
};

