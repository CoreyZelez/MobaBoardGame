#pragma once
#include <SFML/Graphics.hpp>
#include "MouseInputDetection.h"
#include "TextUtility.h"



class ActionText
{
public:

protected:
	ActionText(sf::Text &text);
	virtual void action() {};  // What the text does when clicked on.

private:
	sf::Text &text;
};

