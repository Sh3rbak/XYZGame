#include "FewHitPointsBlock.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	FewHitPointsBlock::FewHitPointsBlock(const sf::Vector2f& position, int hitPoints) :
		SmoothDestroyableBlock(position)
	{
		color += sf::Color::Red;
		sprite.setColor(color);
		hitCount = hitPoints;
	}

	void FewHitPointsBlock::ChangePhaseBlock()
	{
		if (hitCount == 0)
		{
			return;
		}
		sf::Color blockColor = sprite.getColor();
		blockColor.r -= blockColor.r / hitCount;
		color = blockColor;
		sprite.setColor(color);
	}

	void FewHitPointsBlock::OnHit()
	{
		--hitCount;
		ChangePhaseBlock();
		if (hitCount == 0)
		{
			hitCount = 1;
			StartTimer(SETTINGS.BREAK_DELAY);
		}
	}
}