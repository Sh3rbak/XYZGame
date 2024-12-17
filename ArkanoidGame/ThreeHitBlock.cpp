#include "ThreeHitBlock.h"
#include "GameSettings.h"
#include "ScoreManager.h"


namespace ArkanoidGame {

	ThreeHitBlock::ThreeHitBlock(const sf::Vector2f& position)
		: SmoothDestroyableBlock(position, sf::Color::Magenta)
	{
		hitCount = 3;
	}

	void ThreeHitBlock::OnHit() {
		--hitCount;
		StageChange();

		if (hitCount == 0) {
			hitCount = 1;
			StartTimer(SETTINGS.BREAK_DELAY);
			ScoreManager::Instance().AddPoints(SETTINGS.POINTS_FOR_BLOCK * 3);
		}
	}

	void ThreeHitBlock::StageChange() {

		if (hitCount == 2)
			sprite.setColor(sf::Color::Red);
		if (hitCount < 2) {
			sprite.setColor(sf::Color::Green);
			color = sf::Color::Green;
		}
	}
}
