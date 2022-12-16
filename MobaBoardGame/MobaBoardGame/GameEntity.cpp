#include "GameEntity.h"
#include <iostream>

GameEntity::GameEntity(Team team)
	: team(team), image(position, team)
{
}

GameEntity::GameEntity(Team team, sf::Color left, sf::Color right)
	: team(team), image(position, team, left, right)
{
}

void GameEntity::initName(std::string name)
{
	this->name = name;
}

Team GameEntity::getTeam()
{
	return team;
}

std::string GameEntity::getName()
{
	return name;
}

Position GameEntity::getPosition() const
{
	return position;
}

bool GameEntity::isAt(float x, float y) const
{
	return image.isAt(x, y);
}

void GameEntity::draw(sf::RenderWindow & window)
{
	image.draw(window);
}

void GameEntity::move(Position position)
{
	this->position = position;
	image.updatePosition(position);
}

void GameEntity::setHealth(const int & currHealth, const int maxHealth)
{
	image.setHealth(currHealth, maxHealth);
}

