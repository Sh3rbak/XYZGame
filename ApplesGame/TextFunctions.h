#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
	void InitText(sf::Text& text, const sf::Font& font, const std::string& string,
		const int& size, const sf::Color& color, const Position2D& position);
}

