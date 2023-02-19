#include "GameEntity.h"
#include <iostream>

GameEntity::GameEntity(Team team, ActiveEntityImage image)
	: team(team), image(image)
{
}

void GameEntity::initName(std::string name)
{
	this->name = name;
}

Team GameEntity::getTeam() const
{
	return team;
}

std::string GameEntity::getName() const
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

bool GameEntity::isAt(Position position) const
{
	return (this->position.x == position.x && this->position.y == position.y);
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

void GameEntity::setHealth(const int &currHealth, const int &maxHealth)
{
	image.setHealth(currHealth, maxHealth);
}

