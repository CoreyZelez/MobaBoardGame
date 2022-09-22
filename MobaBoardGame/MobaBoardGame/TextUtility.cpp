#include "TextUtility.h"

void centerText(sf::Text &text, const sf::RenderWindow &window, const int yDisplacement)
{
	const int x = (window.getSize().x - text.getGlobalBounds().width) / 2;
	const int y = (window.getSize().y - text.getGlobalBounds().height) / 2 + yDisplacement;
	text.setPosition(sf::Vector2f(x, y));
}

void drawTextRect(const sf::Text &text, sf::RenderWindow &window)
{
	auto rect = text.getGlobalBounds();
	sf::RectangleShape shape(sf::Vector2f(rect.width, rect.height));
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	window.draw(shape);
}


