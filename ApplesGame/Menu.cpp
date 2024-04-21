#include "Menu.h"
#include "Game.h"

namespace ApplesGame
{
	void InitTextMenu(sf::Text& text, const sf::Font& font, const std::string& string,
		const int& size, const sf::Color& color, const Position2D& position)
	{
		text.setFont(font);
		text.setString(string);
		text.setCharacterSize(size);
		text.setFillColor(color);
		text.setOrigin(GetTextOrigin(text, { 0.5f, 0.5f }));
		text.setPosition(position.x, position.y);
	}
	void InitMenu(Menu& menu, const sf::Font& font)
	{
		InitTextMenu(menu.titleText, font, "APPLES GAME!", 60, sf::Color::White, { SCREEN_WIDHT / 2, SCREEN_HEIGHT / 4 });
		InitTextMenu(menu.subtitleText, font, "Num to select Game Mode, Space to New Game", 
			20, sf::Color::White, { SCREEN_WIDHT / 2, SCREEN_HEIGHT / 3 }); 
		InitTextMenu(menu.accelerationSpeedText, font, "1. Accelaretion Speed : On", 
			30, sf::Color::White, { SCREEN_WIDHT / 2, SCREEN_HEIGHT / 2 });
		InitTextMenu(menu.infiniteApplesText, font, "2. Infinite Apples : On", 
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
		
		if (gameMode & GameModeMask::accelerationSpeed)
		{
			menu.accelerationSpeedText.setString("1. Accelaretion Speed : On");
		}
		else
		{
			menu.accelerationSpeedText.setString("1. Accelaretion Speed : Off");
		}

		if (gameMode & GameModeMask::infiniteApples)
		{
			menu.infiniteApplesText.setString("2. Infinite Apples : On");
		}
		else
		{
			menu.infiniteApplesText.setString("2. Infinite Apples : Off");
		}
	}
	void DrawMenu(Menu& menu, sf::RenderWindow& window)
	{
		window.draw(menu.titleText);
		window.draw(menu.subtitleText);
		window.draw(menu.accelerationSpeedText);
		window.draw(menu.infiniteApplesText);

	}
}