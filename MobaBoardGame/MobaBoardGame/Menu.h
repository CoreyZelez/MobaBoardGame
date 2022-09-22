#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "MouseInputDetection.h"


enum MenuType
{
	mainMenu,
	newGameMenu,
	loadGameMenu,
	mapCreatorMenu
};

class Menu
{
public:
	Menu();

	void draw(sf::RenderWindow &window);

private:
	MenuType currentMenu;
	sf::Font font;

	void drawMainMenu(sf::RenderWindow &window);
	void drawNewGameMenu(sf::RenderWindow &window);
	void drawMapCreatorMenu(sf::RenderWindow &window);
};


