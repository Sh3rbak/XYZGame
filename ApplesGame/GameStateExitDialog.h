#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"

namespace ApplesGame
{
	struct Game;

	struct GameStateExitDialogData
	{
		sf::Font font;

		sf::RectangleShape background;

		MenuItem continueText;
		MenuItem exitToMenuText;

		Menu menu;
	};

	void InitGameStateExitDialog(GameStateExitDialogData& data, Game& game);
	void ShutdownGameStateExitDialog(GameStateExitDialogData& data, Game& game);
	void HandleGameStateExitDialogWindowEvent(GameStateExitDialogData& data, Game& game, const sf::Event& event);
	void UpdateGameStateExitDialog(GameStateExitDialogData& data, Game& game, float timeDelta);
	void DrawGameStateExitDialog(GameStateExitDialogData& data, Game& game, sf::RenderWindow& window);
}
