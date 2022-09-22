#include <iostream>
#include "Menu.h"
#include "TextUtility.h"
#include "MouseInputDetection.h"


Menu::Menu()
	: currentMenu(mainMenu)
{
	font.loadFromFile("Aller_Bd.ttf");
}


/* Draws current menu that user is in and handles transitions between
each type of menu.
*/
void Menu::draw(sf::RenderWindow &window)
{
	switch(currentMenu)
	{
	case mainMenu:
		drawMainMenu(window);
		break;

	case newGameMenu:
		drawNewGameMenu(window);
		break;

	case mapCreatorMenu:
		std::cout << 1;
		drawMapCreatorMenu(window);
		break;
	}
}


void Menu::drawMainMenu(sf::RenderWindow &window)
{
	MouseInputDetection midet(window);

	sf::Text text1("New Game", font, 40);
	sf::Text text2("Load Game", font, 40);
	sf::Text text3("Map Creator", font, 40);

	centerText(text1, window, -10);
	centerText(text2, window, 40);
	centerText(text3, window, 90);

	window.draw(text1);
	window.draw(text2);
	window.draw(text3);

	// Determines which menu to transition to.
	if(midet.textLeftClick(text1))
	{
		currentMenu = newGameMenu;
	}
	else if(midet.textLeftClick(text2))
	{

	}
	else if(midet.textLeftClick(text3))
	{
		currentMenu = mapCreatorMenu;
	}
}

void Menu::drawNewGameMenu(sf::RenderWindow &window)
{

}

void Menu::drawMapCreatorMenu(sf::RenderWindow &window)
{
	sf::Text text1("Enter the maps file name", font, 40);
	centerText(text1, window, 20);
	window.draw(text1);
}





