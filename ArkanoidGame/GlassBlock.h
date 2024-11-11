#pragma once
#include <SFML/Graphics.hpp>
#include "Block.h"

namespace ArkanoidGame
{
	class GlassBlock final : public Block
	{
	public:
		GlassBlock(const sf::Vector2f& position, const sf::Color& color = sf::Color::White);
		~GlassBlock() = default;
		bool CheckCollision(std::shared_ptr<Colladiable> collidable) override;
	};
}

