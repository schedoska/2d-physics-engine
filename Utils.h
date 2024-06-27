#pragma once

#include <SFML/Graphics.hpp>
#include "Vector.h"

namespace dm2 
{
	sf::Vector2f ConvertToVector2F(const dm2::Vector& vector);
	float RadToDegrees(const float radians);

	void drawLine(dm2::Vector start, dm2::Vector end, sf::RenderWindow& window, sf::Color color = sf::Color::Cyan);
	void drawPoint(dm2::Vector point, sf::RenderWindow& window);
}

