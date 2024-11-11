#pragma once
#include <SFML/Graphics.hpp>
#include "Block.h"

namespace ArkanoidGame
{
	class FewHitPointsBlock final : public SmoothDestroyableBlock
	{
	public:
		FewHitPointsBlock(const sf::Vector2f& position, int hitPoints);
		~FewHitPointsBlock() = default;
		void ChangePhaseBlock();

	private:
		void OnHit() override;
	};
}

