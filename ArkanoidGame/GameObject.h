#pragma once
#include <SFML/Graphics.hpp>

namespace ArcanoidGame
{
	class GameObject
	{
	public:
		void Draw(sf::RenderWindow& window);

		sf::FloatRect GetRect() const { return sprite.getGlobalBounds(); }
		sf::Vector2f GetPosition() const { return sprite.getPosition(); }
	protected:
		sf::Sprite sprite;
		sf::Texture texture;
	};
}

