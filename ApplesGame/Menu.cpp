#include "Menu.h"
#include "Game.h"

namespace ApplesGame
{
	void InitMenu(Menu& menu, const sf::Font& font)
	{
		InitText(menu.titleText, font, "APPLES GAME!", 60, sf::Color::White, { SCREEN_WIDHT / 2, SCREEN_HEIGHT / 4 });
		InitText(menu.subtitleText, font, "Num to select Game Mode, Space to New Game", 
			20, sf::Color::White, { SCREEN_WIDHT / 2, SCREEN_HEIGHT / 3 }); 
		InitText(menu.accelerationSpeedText, font, "1. Accelaretion Speed : On", 
			30, sf::Color::White, { SCREEN_WIDHT / 2, SCREEN_HEIGHT / 2 });
		InitText(menu.infiniteApplesText, font, "2. Infinite Apples : On", 
			30, sf::Color::White, { SCREEN_WIDHT / 2, SCREEN_HEIGHT / 2 + 50.f });
	}
	void UpdateMenu(Menu& menu, int& gameMode, const float& deltaTime)
	{
		menu.buttonPause += deltaTime;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && menu.buttonPause > BUTTON_PAUSE)
		{
			gameMode ^= GameModeMask::accelerationSpeed;
			menu.buttonPause = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && menu.buttonPause > BUTTON_PAUSE)
		{
			gameMode ^= GameModeMask::infiniteApples;
			menu.buttonPause = 0;
		}
		
		bool isAccelerationSpeed = gameMode & GameModeMask::accelerationSpeed;
		bool isInfiniteApples = gameMode & GameModeMask::infiniteApples;
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