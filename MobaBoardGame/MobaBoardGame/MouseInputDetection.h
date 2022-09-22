#pragma once
#include <SFML/Graphics.hpp>

class MouseInputDetection
{
public:
	MouseInputDetection(const sf::RenderWindow &window);

	bool rectangleLeftClick(const sf::IntRect &rect) const;  // Single click detection on rectangle.
	bool rectangleLeftClick(const sf::FloatRect &rect) const;  
	bool textLeftClick(const sf::Text &text) const;  // Single click detection on text.

	static void update();  // Updates all member variables.

private:
	static void unlockLeftClick();  // Checks whether button is pressed and updates member accordingly.

	const sf::RenderWindow &window;

	static bool lockLeftClick;  // For detection of mouse click (not hold).
};

