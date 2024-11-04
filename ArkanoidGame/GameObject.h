#pragma once
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
	class GameObject
	{
	public:
		virtual ~GameObject() = default;

		virtual void Init() = 0;
		virtual void Update(float timeDelta) = 0;
		virtual void Draw(sf::RenderWindow& window);

		sf::FloatRect GetRect() const { return sprite.getGlobalBounds(); }
		sf::Vector2f GetPosition() const { return sprite.getPosition(); }
	protected:
		sf::Sprite sprite;
		sf::Texture texture;
	};
}

