#include "UIGame.h"

namespace ApplesGame
{
	void InitUIGame(UIGame& uiGame, const sf::Font& font)
	{
		InitText(uiGame.controlPlayerText, font, "Arrow to Move, TAB to Menu, ESC to Exit",
			24, sf::Color::White, { SCREEN_WIDHT * (12.f / 15.f), 20.f });
		InitText(uiGame.scorePlayerText, font, "Your score : 0",
			24, sf::Color::White, { SCREEN_WIDHT / 13.f, 20.f});

		InitText(uiGame.gameOverText, font, "Game Over!",
			50, sf::Color::White, { SCREEN_WIDHT / 2.f, SCREEN_HEIGHT / 2.5f });
		InitText(uiGame.gameOverScoreText, font, "Your score : 0",
			30, sf::Color::White, { SCREEN_WIDHT / 2.f, SCREEN_HEIGHT / 2.f });

		InitLeaderBoard(uiGame.leaderBoard, font);
	}

	void UpdateUIGame(UIGame& uiGame, const int score, const float finishPauseTime)
	{
		uiGame.scorePlayerText.setString("Your score : " + std::to_string(score));

		uiGame.gameOverText.setFillColor((int)finishPauseTime % 2 ? sf::Color::White : sf::Color::Yellow);
		uiGame.gameOverScoreText.setString("Your score : " + std::to_string(score));

		UpdateLeaderBoard(uiGame.leaderBoard);
	}

	void DrawUIGame(UIGame& uiGame, sf::RenderWindow& window, const bool isGameFinished)
	{
		window.draw(uiGame.controlPlayerText);
		window.draw(uiGame.scorePlayerText);
		if (isGameFinished)
		{
			window.draw(uiGame.gameOverText);
			window.draw(uiGame.gameOverScoreText);
			DrawLeaderBoard(uiGame.leaderBoard, window);
		}
	}
}
