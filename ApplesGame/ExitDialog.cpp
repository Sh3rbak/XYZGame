#include "ExitDialog.h"

namespace ApplesGame
{
	void InitExitDialog(ExitDialog& exitDialog, const sf::Font& font)
	{
		exitDialog.backround.setSize(sf::Vector2f(SCREEN_WIDHT / 3, SCREEN_HEIGHT / 3));
		exitDialog.backround.setFillColor(sf::Color::Black);
		sf::FloatRect localOrigin = exitDialog.backround.getLocalBounds();
		sf::Vector2f reqOrigin;
		reqOrigin.x = localOrigin.width / 2;
		reqOrigin.y = localOrigin.height / 2;
		exitDialog.backround.setOrigin(reqOrigin);
		exitDialog.backround.setPosition(sf::Vector2f(SCREEN_WIDHT / 2.f, SCREEN_HEIGHT / 2.f));
		exitDialog.backround.setOutlineThickness(5.f);
		exitDialog.backround.setOutlineColor(sf::Color::White);
		InitText(exitDialog.titleText, font, "Do you want to exit?", 40, sf::Color::White,
			{ SCREEN_WIDHT / 2.f, SCREEN_HEIGHT / 2.5f }, { 0.5f, 0.5f });
		InitText(exitDialog.noText, font, "1.No", 30, sf::Color::White,
			{ SCREEN_WIDHT / 2.3f, SCREEN_HEIGHT / 1.8f }, { 0.5f, 0.5f });
		InitText(exitDialog.yesText, font, "2.Yes", 30, sf::Color::White,
			{ SCREEN_WIDHT / 1.8f, SCREEN_HEIGHT / 1.8f }, { 0.5f, 0.5f });
	}

	void DrawExitDialog(ExitDialog& exitDialog, sf::RenderWindow& window)
	{
		window.draw(exitDialog.backround);
		window.draw(exitDialog.titleText);
		window.draw(exitDialog.noText);
		window.draw(exitDialog.yesText);
	}
}