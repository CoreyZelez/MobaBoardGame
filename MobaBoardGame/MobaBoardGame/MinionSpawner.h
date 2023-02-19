#pragma once
#include <vector>
#include <memory>
#include "Team.h"
#include "Position.h"

class Game;
class GameBoard;
class Minion;

class MinionSpawner
{
public:
	MinionSpawner(Game &game, Team team, std::vector<Position> minionPath);

	void update();

	void levelUp();

	bool canSpawn();
	std::unique_ptr<Minion> spawnMinion();

private:
	// Timing.
	const int spawnTime = 18;
	int time = 14;  // Starts at 3 so minions don't spawn immediately (for testing).

	// Minion information.
	int minionLevel = 1;  // Level of minions spawned.
	const std::vector<Position> minionPath;
	Team team;

	Game &game;
	GameBoard &gameBoard;
};

