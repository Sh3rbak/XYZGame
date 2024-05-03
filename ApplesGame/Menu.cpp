#include "Menu.h"
#include "Game.h"

namespace ApplesGame
{
	void InitMenu(Menu& menu, const sf::Font& font)
	{
		InitText(menu.titleText, font, "APPLES GAME!", 60, sf::Color::White, 
			{ SCREEN_WIDHT / 2, SCREEN_HEIGHT / 4 }, { 0.5f , 0.5f });
		InitText(menu.subtitleText, font, "Num to select Game Mode, Space to New Game", 
			20, sf::Color::White, { SCREEN_WIDHT / 2, SCREEN_HEIGHT / 3 }, { 0.5f , 0.5f });
		InitText(menu.accelerationSpeedText, font, "1. Accelaretion Speed : On", 
			30, sf::Color::White, { SCREEN_WIDHT / 2, SCREEN_HEIGHT / 2 }, { 0.5f , 0.5f });
		InitText(menu.infiniteApplesText, font, "2. Infinite Apples : On", 
			30, sf::Color::White, { SCREEN_WIDHT / 2, SCREEN_HEIGHT / 2 + 50.f }, { 0.5f , 0.5f });
	}

	void UpdateMenu(Menu& menu, const struct Game& game)
	{		
		bool isAccelerationSpeed = (std::uint8_t)game.options & (std::uint8_t)GameOptions::accelerationSpeed;
		bool isInfiniteApples = (std::uint8_t)game.options & (std::uint8_t)GameOptions::infiniteApples;
		sf::String textForSelectGameMode = "1. Acceleration Speed : " + sf::String(isAccelerationSpeed ? "On" : "Off");
		menu.accelerationSpeedText.setString(textForSelectGameMode);
		textForSelectGameMode = "2. Infinite Apples : " + sf::String(isInfiniteApples ? "On" : "Off");
		menu.infiniteApplesText.setString(textForSelectGameMode);
	}

	void DrawMenu(Menu& menu, sf::RenderWindow& window)
	{
		window.draw(menu.titleText);
		window.draw(menu.subtitleText);
		window.draw(menu.accelerationSpeedText);
		window.draw(menu.infiniteApplesText);
	}
}