#include "TextFunctions.h"

namespace ApplesGame
{
	void InitText(sf::Text& text, const sf::Font& font, const std::string& string,
		const int& size, const sf::Color& color, const Position2D& position, const Position2D& origin)
	{
		text.setFont(font);
		text.setString(string);
		text.setCharacterSize(size);
		text.setFillColor(color);
		text.setOrigin(GetTextOrigin(text, origin));
		text.setPosition(position.x, position.y);
	}
	void UpdateText(sf::Text& text, const std::string& string, const Position2D& originText)
	{
		text.setString(string);
		text.setOrigin(GetTextOrigin(text, originText));
	}
}