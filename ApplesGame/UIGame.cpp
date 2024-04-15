#include "UIGame.h"
#include <string>

namespace ApplesGame
{
	void InitText(sf::Text& text, const sf::Font& font, const std::string& string, 
		const int& size, const sf::Color& color, const Position2D& position)
	{
		text.setFont(font);
		text.setString(string);
		text.setCharacterSize(size);
		text.setFillColor(color);
		text.setOrigin(GetTextOrigin(text, { 0.5f, 0.5f }));
		text.setPosition(position.x, position.y);
	}

	void InitUIGame(UIGame& uiGame, const sf::Font& font)
	{
		InitText(uiGame.controlPlayerText, font, "Arrow to Move, ESC to Exit",
			24, sf::Color::White, { SCREEN_WIDHT * (13.f / 15.f), 20.f });
		InitText(uiGame.scorePlayerText, font, "Your score : 0",
			24, sf::Color::White, { SCREEN_WIDHT / 13.f, 20.f});

		InitText(uiGame.gameOverText, font, "Game Over!",
			50, sf::Color::White, { SCREEN_WIDHT / 2.f, SCREEN_HEIGHT / 2.5f });
		InitText(uiGame.gameOverScoreText, font, "Your score : 0",
			30, sf::Color::White, { SCREEN_WIDHT / 2.f, SCREEN_HEIGHT / 2.f });
	}

	void UpdateUIGame(UIGame& uiGame, const int score, const float finishPauseTime)
	{
		uiGame.scorePlayerText.setString("Your score : " + std::to_string(score));

		uiGame.gameOverText.setFillColor((int)finishPauseTime % 2 ? sf::Color::White : sf::Color::Yellow);
		uiGame.gameOverScoreText.setString("Your score : " + std::to_string(score));
	}

	void DrawUIGame(UIGame& uiGame, sf::RenderWindow& window, const bool isGameFinished)
	{
		window.draw(uiGame.controlPlayerText);
		window.draw(uiGame.scorePlayerText);
		if (isGameFinished)
		{
			window.draw(uiGame.gameOverText);
			window.draw(uiGame.gameOverScoreText);
		}
	}
}
