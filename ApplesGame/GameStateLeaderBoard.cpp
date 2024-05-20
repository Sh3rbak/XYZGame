#include "GameStateLeaderBoard.h"
#include <assert.h>
#include "Game.h"

namespace ApplesGame
{
	void InitGameStateLeaderBoard(GameStateLeaderBoard& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		data.recordsTableText.setFont(data.font);
		data.recordsTableText.setCharacterSize(24);
		data.recordsTableText.setFillColor(sf::Color::White);
		data.recordsTableText.setString("Records:\nPlayer: 999\nPlayer: 999\nPlayer: 999\nPlayer: 999\nPlayer: 999");
		data.recordsTableText.setOrigin(GetItemOrigin(data.recordsTableText, { 0.5f, 0.f }));

		game.recordsTable["Player"] = 0;
	}
	void ShutdownGameStateLeaderBoard(GameStateLeaderBoard& data, Game& game)
	{
	}
	void HandleGameStateLeaderBoardWindowEvent(GameStateLeaderBoard& data, Game& game, const sf::Event& event)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			SwitchGameState(game, GameStateType::MainMenu);
		}
	}
	void UpdateGameStateLeaderBoard(GameStateLeaderBoard& data, Game& game)
	{
		data.recordsTableText.setString("Leader Board:\n");
		for (const auto& item : game.recordsTable)
		{
			data.recordsTableText.setString(data.recordsTableText.getString() + "\n" + item.first + ": " + std::to_string(item.second));
		}
		data.recordsTableText.setOrigin(GetItemOrigin(data.recordsTableText, { 0.5f, 0.f }));
	}
	void DrawGameStateLeaderBoard(GameStateLeaderBoard& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		data.recordsTableText.setPosition(viewSize.x / 2.f, viewSize.y / 3.f);
		window.draw(data.recordsTableText);
	}
}

