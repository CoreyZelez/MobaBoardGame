#include "MinionAttributesSystem.h"
#include "MinionEffectsManager.h"
#include <iostream>

MinionAttributesSystem::MinionAttributesSystem(Minion &minion, int level, std::vector<EntityAttributes> coreBaseAttributes)
	: AttributesSystem<Minion>(std::make_unique<MinionEffectsManager>(minion), coreBaseAttributes)
{
}
