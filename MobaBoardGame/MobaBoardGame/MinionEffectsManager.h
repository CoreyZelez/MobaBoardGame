#pragma once
#include "EffectsManager.h"

class Minion;

class MinionEffectsManager : public EffectsManager<Minion>
{
public:
	MinionEffectsManager(Minion &minion);

	void update();  // Calls update on each effect.
};

