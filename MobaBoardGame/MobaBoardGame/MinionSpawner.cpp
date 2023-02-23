#include "MinionSpawner.h"
#include "Game.h"

MinionSpawner::MinionSpawner(Game &game, Team team, std::vector<Position> minionPath)
	: minionPath(minionPath), team(team), gameBoard(game.getBoard()), game(game)
{
}

void MinionSpawner::update()
{
	assert(time < spawnTime);
	++time;
}

void MinionSpawner::levelUp()
{
	++minionLevel;
}

bool MinionSpawner::canSpawn()
{
	return time == spawnTime;
}

std::shared_ptr<Minion> MinionSpawner::spawnMinion()
{
	assert(time == spawnTime);
	time = 0;

	HealthAttributes ha1 = { 550, 0 };  // hp, hpRegen
	HealthAttributes ha2 = { 580, 0 };
	HealthAttributes ha3 = { 610, 0 };
	HealthAttributes ha4 = { 640, 0 };
	HealthAttributes ha5 = { 670, 0 };
	HealthAttributes ha6 = { 700, 0 };

	CombatAttributes ca1 = { 26, 10, 10, 10 };  // phyDmg, armorPen, lethality, armor
	CombatAttributes ca2 = { 27, 12, 12, 12 };
	CombatAttributes ca3 = { 28, 14, 14, 14 };
	CombatAttributes ca4 = { 29, 16, 16, 16 };
	CombatAttributes ca5 = { 30, 18, 18, 18 };
	CombatAttributes ca6 = { 31, 20, 20, 20 };

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

	std::vector<EntityAttributes> coreBaseAttributes = { cha1, cha2, cha3, cha4, cha5, cha6 };

	return std::make_shared<Minion>(game, team, minionPath, minionLevel, coreBaseAttributes);
}
