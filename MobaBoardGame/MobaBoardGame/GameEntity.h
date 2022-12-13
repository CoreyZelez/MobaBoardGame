#pragma once
#include <list>
#include <array>
#include <string>
#include "EntityAttributes.h"
#include "CharacterAbilities.h"
#include "Effect.h"
#include "Item.h"
#include "Position.h"
#include "Team.h"
#include "GameBoard.h"
#include "ActiveEntityImage.h"


/* An GameEntity is an entity that can occupy an OccupiableSquare such that no other ActiveEntities may also 
   occupy the given square. Examples include characters, creatures or towres. */
class GameEntity
{
	using EntityEffect = Effect<EntityAttributes>;

public:
	GameEntity(Team team, sf::Color left, sf::Color right);
	void initName(std::string name);

	Team getTeam();
	std::string getName();
	Position getPosition() const;

	bool isAt(float x, float y) const;

	void draw(sf::RenderWindow &window);

	virtual void move(Position position);  

protected:
	void setHealth(const int &currHealth, const int maxHealth);  // Only to be called on entities containing health. 

private:
	std::string name;
	Team team;
	Position position = { 0, 0 };  // Default value for initialisation.
	ActiveEntityImage image;
};

