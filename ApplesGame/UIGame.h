#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"
#include "TextFunctions.h"

namespace ApplesGame
{
	struct UIGame
	{
		sf::Text scorePlayerText;
		sf::Text controlPlayerText;
		sf::Text gameOverText;
		sf::Text gameOverScoreText;
	};

	void InitUIGame(UIGame& uiGame, const sf::Font& font);
	void UpdateUIGame(UIGame& uiGame, const int score, const float finishPauseTime);
	void DrawUIGame(UIGame& uiGame, sf::RenderWindow& window, const bool isGameFinished);
}
