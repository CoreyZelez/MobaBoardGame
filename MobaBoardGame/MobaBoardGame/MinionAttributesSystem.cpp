#include "MinionAttributesSystem.h"
#include "MinionEffectsManager.h"
#include <iostream>

HealthAttributes ha1 = { 360, 0 };  // hp, hpRegen
HealthAttributes ha2 = { 430, 0 };
HealthAttributes ha3 = { 550, 0 };
HealthAttributes ha4 = { 610, 0 };
HealthAttributes ha5 = { 740, 0 };
HealthAttributes ha6 = { 880, 0 };

CombatAttributes ca1 = { 51, 10, 5, 20 };  // phyDmg, armorPen, lethality, armor
CombatAttributes ca2 = { 59, 12, 9, 28 };
CombatAttributes ca3 = { 62, 15, 26, 40 };
CombatAttributes ca4 = { 70, 17, 31, 44 };
CombatAttributes ca5 = { 82, 20, 34, 50 };
CombatAttributes ca6 = { 88, 25, 40, 65 };

ActionAttributes aca = { 1, 1, 1, 1, 1, 1 };  // points, movPoints, attPoints, movCost, attCost, range

AbilityAttributes aa1 = { 0, 0, 0 };  // abilityPower, abiltyPen, abilityResist
AbilityAttributes aa2 = { 0, 0, 0 };
AbilityAttributes aa3 = { 0, 0, 0 };
AbilityAttributes aa4 = { 0, 0, 0 };
AbilityAttributes aa5 = { 0, 0, 0 };
AbilityAttributes aa6 = { 0, 0, 0 };

EntityAttributes cha1 = { aca, ha1, ca1, aa1 };
EntityAttributes cha2 = { aca, ha2, ca2, aa2 };
EntityAttributes cha3 = { aca, ha3, ca3, aa3 };
EntityAttributes cha4 = { aca, ha4, ca4, aa4 };
EntityAttributes cha5 = { aca, ha5, ca5, aa5 };
EntityAttributes cha6 = { aca, ha6, ca6, aa6 };

const std::vector<EntityAttributes> coreBaseAttributes = { cha1, cha2, cha3, cha4, cha5, cha6 };

MinionAttributesSystem::MinionAttributesSystem(Minion &minion, int level)
	: AttributesSystem<Minion>(std::make_unique<MinionEffectsManager>(minion), coreBaseAttributes)
{
}
