#include "GlassBlock.h"
#include <cassert>

namespace ArkanoidGame
{
	GlassBlock::GlassBlock(const sf::Vector2f& position, const sf::Color& color):
		Block(position, color)
	{
	}

	bool GlassBlock::CheckCollision(std::shared_ptr<Colladiable> collidable)
	{
		if (GetCollision(collidable)) {
			OnHit();
		}
		return false;
	}

}