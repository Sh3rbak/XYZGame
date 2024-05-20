#pragma once
#include "SFML/Graphics.hpp"
#include "GameSettings.h"

namespace ApplesGame
{
	struct Game;
	struct GameStateLeaderBoard
	{
		sf::Font font;
		sf::Text recordsTableText;
	};
	void InitGameStateLeaderBoard(GameStateLeaderBoard& data, Game& game);
	void ShutdownGameStateLeaderBoard(GameStateLeaderBoard& data, Game& game);
	void HandleGameStateLeaderBoardWindowEvent(GameStateLeaderBoard& data, Game& game, const sf::Event& event);
	void UpdateGameStateLeaderBoard(GameStateLeaderBoard& data, Game& game);
	void DrawGameStateLeaderBoard(GameStateLeaderBoard& data, Game& game, sf::RenderWindow& window);
}

