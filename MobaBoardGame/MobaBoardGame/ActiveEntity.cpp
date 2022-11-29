#include "ActiveEntity.h"
#include <iostream>

ActiveEntity::ActiveEntity(Position position)
	: position(position), image(position)
{
	
}

void ActiveEntity::initName(std::string name)
{
	this->name = name;
}

void ActiveEntity::initTeam(Team team)
{
	this->team = team;
	image.initBackColor(team);
}

void ActiveEntity::initImageColors(sf::Color left, sf::Color right)
{
	image.initLeftColor(left);
	image.initRightColor(right);
}

Team ActiveEntity::getTeam()
{
	return team;
}

std::string ActiveEntity::getName()
{
	return name;
}

Position ActiveEntity::getPosition() const
{
	return position;
}

bool ActiveEntity::isAt(float x, float y) const
{
	return image.isAt(x, y);
}

void ActiveEntity::draw(sf::RenderWindow & window)
{
	image.draw(window);
}

void ActiveEntity::move(Position position)
{
	this->position = position;
	image.updatePosition(position);
}

