#pragma once
#include "EntityAttributes.h"
#include "AttributesSystem.h"

class Minion;

class MinionAttributesSystem : public AttributesSystem<Minion>
{
public:
	MinionAttributesSystem(Minion &minion, int level);

	//void merge(MinionAttributesSystem);

};

