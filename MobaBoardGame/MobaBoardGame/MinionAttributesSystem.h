#pragma once
#include "EntityAttributes.h"
#include "AttributesSystem.h"

class Minion;

class MinionAttributesSystem : public AttributesSystem<Minion>
{
public:
	MinionAttributesSystem(Minion &minion, int level, std::vector<EntityAttributes> coreBaseAttributes);

	//void merge(MinionAttributesSystem);
private:
	std::vector<EntityAttributes> coreBaseAttributes;
};

