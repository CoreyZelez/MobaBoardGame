#include "MouseInputDetection.h"
#include <iostream>


bool MouseInputDetection::lockLeftClick = false;

MouseInputDetection::MouseInputDetection(const sf::RenderWindow &window)
	: window(window)
{
}

bool MouseInputDetection::rectangleLeftClick(const sf::IntRect &rect) const
{
	if(lockLeftClick || !sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		return false;
	}

	return rect.contains(sf::Mouse::getPosition());
}

bool MouseInputDetection::rectangleLeftClick(const sf::FloatRect &rect) const
{
	if(lockLeftClick || !sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		return false;
	}

	const float x = window.mapPixelToCoords(sf::Mouse::getPosition(window)).x;
	const float y = window.mapPixelToCoords(sf::Mouse::getPosition(window)).y;
	return rect.contains(x, y);
}

bool MouseInputDetection::textLeftClick(const sf::Text &text) const
{
	const auto rect = text.getGlobalBounds();
	return rectangleLeftClick(rect);
}

void MouseInputDetection::update()
{
	unlockLeftClick();
}

void MouseInputDetection::unlockLeftClick()
{
	if(!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		lockLeftClick = false;
	}
}
