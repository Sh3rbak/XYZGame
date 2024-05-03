#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Math.h"
#include "TextFunctions.h"

namespace ApplesGame
{
	struct Menu
	{
		sf::Text titleText;
		sf::Text subtitleText;
		sf::Text accelerationSpeedText;
		sf::Text infiniteApplesText;
		float buttonPause = 0;
	};

	void InitMenu(Menu& menu, const sf::Font& font);
	void UpdateMenu(Menu& menu, const struct Game& game);
	void DrawMenu(Menu& menu, sf::RenderWindow& window);
}
