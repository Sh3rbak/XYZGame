#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Math.h"
#include "TextFunctions.h"

namespace ApplesGame
{
	struct ExitDialog
	{
		sf::RectangleShape backround;
		sf::Text titleText;
		sf::Text yesText;
		sf::Text noText;
	};
	void InitExitDialog(ExitDialog& exitDialog, const sf::Font& font);
	void DrawExitDialog(ExitDialog& exitDialog, sf::RenderWindow& window);
};
