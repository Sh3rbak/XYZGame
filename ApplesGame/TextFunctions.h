#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
	void InitText(sf::Text& text, const sf::Font& font, const std::string& string,
		const int& size, const sf::Color& color, const Position2D& position, const Position2D& origin);
	void UpdateText(sf::Text& text, const std::string& string, const Position2D& originText = { 0.5f, 0.5f });
}

