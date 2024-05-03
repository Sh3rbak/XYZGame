#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Math.h"
#include "TextFunctions.h"
#include "LeaderBoard.h"

namespace ApplesGame
{
	struct UI
	{
		int score = 0;

		sf::Text scorePlayerText;
		sf::Text controlPlayerText;
		sf::Text gameOverText;
		sf::Text gameOverScoreText;

		LeaderBoard leaderBoard;
	};

	void InitUI(UI& UI, const sf::Font& font);
	void UpdateUI(UI& UI, const float finishPauseTime);
	void DrawUI(UI& UI, sf::RenderWindow& window, const bool isGameFinished);
	void SetScoreInUI(UI& UI, int score);
}
