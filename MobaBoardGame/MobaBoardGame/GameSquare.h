#pragma once
#include <SFML/Graphics.hpp>
#include "Position.h"
#include "SquareType.h"

const float GRID_SQUARE_SIZE = 100;
const float GRID_OUTLINE_THICKNESS = 5;

class GameEntity;

class GameSquare
{
public:
	GameSquare(Position position, SquareType type, bool occupiable);

	void draw(sf::RenderWindow &window) const;
	virtual void update() {};  // Probably needs game parameter. Updates square based on events or current turn.

	// Getters
	const sf::RectangleShape &getRect() const;
	Position getPosition() const;
	SquareType getType() const;
	const GameEntity *getOccupant() const;
	bool isVacant() const;

	// Setters
	void setOccupant(GameEntity *occupant);
	GameEntity *removeOccupant();  // Return the current occupant.

	// Color changing
	void mark(sf::Color color);
	void unmark();

protected:
	void initSquare();

private:
	// Functions
	// Colors
	void colorSquare();
	void impassableForestColor();  // Colors square for impassable forest.
	void deepWaterColor();  
	void mountainColor();  
	void grassColor();  
	void lavaColor();
	void mountainFloorColor();
	void shallowWaterColor();

	// Occupation members
	GameEntity *occupant = nullptr;  // May be unsettable
	bool occupiable;  // Whether square can be occupied by GameEntity.

	// Square marking members
	bool marked = false;  // When marked is a different color. Can indicate player may move here or use spell.
	sf::Color fillColor;  
	sf::Color outlineColor;

	SquareType type;
	sf::RectangleShape square;
	Position position;
};


