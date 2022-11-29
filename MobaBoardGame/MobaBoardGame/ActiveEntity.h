#pragma once
#include <list>
#include <array>
#include <string>
#include "Attributes.h"
#include "CharacterAbilities.h"
#include "EntityEffects.h"
#include "Effect.h"
#include "Item.h"
#include "Position.h"
#include "Team.h"
#include "ActiveEntityImage.h"


/* An ActiveEntity is an entity that can occupy an OccupiableSquare such that no other ActiveEntities may also 
   occupy the given square. Examples include characters and creatures. Towers are not included as an active entity
   since a character or creature may occupy the same position as a tower.*/
class ActiveEntity
{
	using EntityEffect = Effect<EntityAttributes>;

public:
	ActiveEntity(Position position);
	void initName(std::string name);
	void initTeam(Team team);
	void initImageColors(sf::Color left, sf::Color right);

	Team getTeam();
	std::string getName();
	Position getPosition() const;

	bool isAt(float x, float y) const;

	void draw(sf::RenderWindow &window);

	virtual void move(Position position);  

protected:

private:
	std::string name;
	Team team;
	Position position;
	ActiveEntityImage image;



};

