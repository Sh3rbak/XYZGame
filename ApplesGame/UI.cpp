#include "UI.h"

namespace ApplesGame
{
	void InitUI(UI& UI, const sf::Font& font)
	{
		InitText(UI.controlPlayerText, font, "Arrow to Move, ESC to Menu",
			24, sf::Color::White, { SCREEN_WIDHT * (4.9f / 5.f), 20.f }, {1.f , 0.5f});
		InitText(UI.scorePlayerText, font, "Your score : 0",
			24, sf::Color::White, { SCREEN_WIDHT / 13.f, 20.f}, { 0.5f , 0.5f });

		InitText(UI.gameOverText, font, "Game Over!",
			50, sf::Color::White, { SCREEN_WIDHT / 2.f, SCREEN_HEIGHT / 2.5f }, { 0.5f , 0.5f });
		InitText(UI.gameOverScoreText, font, "Your score : 0",
			30, sf::Color::White, { SCREEN_WIDHT / 2.f, SCREEN_HEIGHT / 2.f }, { 0.5f , 0.5f });

		InitLeaderBoard(UI.leaderBoard, font);
	}

	void SetScoreInUI(UI& UI, int score)
	{
		UI.score = score;
	}

	void UpdateUI(UI& UI, const float finishPauseTime)
	{
		UI.scorePlayerText.setString("Your score : " + std::to_string(UI.score));

		UI.gameOverText.setFillColor((int)finishPauseTime % 2 ? sf::Color::White : sf::Color::Yellow);
		UI.gameOverScoreText.setString("Your score : " + std::to_string(UI.score));

		UpdateLeaderBoard(UI.leaderBoard);
	}

	void DrawUI(UI& UI, sf::RenderWindow& window, const bool isGameFinished)
	{
		window.draw(UI.controlPlayerText);
		window.draw(UI.scorePlayerText);
		if (isGameFinished)
		{
			window.draw(UI.gameOverText);
			window.draw(UI.gameOverScoreText);
			DrawLeaderBoard(UI.leaderBoard, window);
		}
	}
}
