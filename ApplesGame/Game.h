#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameSettings.h"
#include "Math.h"
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "UI.h"
#include "Menu.h"
#include "ExitDialog.h"

namespace ApplesGame
{
	enum class GameOptions : std::uint8_t
	{
		accelerationSpeed = 1 << 0,
		infiniteApples = 1 << 1,

		Default = accelerationSpeed | infiniteApples,
		Empty = 0
	};

	enum class GameState
	{
		None = 0,
		Playing,
		GameOver,
		Menu,
		ExitDialog
	};

	struct Game
	{
		UI UI;
		Menu menu;
		ExitDialog exitDialog;

		GameOptions options = GameOptions::Default;
		Player player;
		std::vector<Apple> apples;
		std::vector<Rock> rocks;

		float gameFinishTime = 0;
		int numEatenApples = 0;
		std::vector<GameState> gameStateStack;

		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture rockTexture;

		sf::SoundBuffer deadPlayerBuf;
		sf::Sound deadPlayerSound;
		sf::SoundBuffer eatAppleBuf;
		sf::Sound eatAppleSound;

		sf::Font font;
	};

	void HandleWindowEvents(Game& game, sf::RenderWindow& window);
	void InitGame(Game& game);
	void UpdateGame(Game& game, float timeDelta);
	void RestartGame(Game& game);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void ShutdownGame(Game& game);

	void PushGameState(Game& game, GameState state);
	void PopGameState(Game& game);
	void SwitchGameState(Game& game, GameState newState);
	void SwitchGameStateInternal(Game& game, GameState oldState, GameState newState);
	GameState GetCurrentGameState(const Game& game);

	void InitPlayingState(Game& game);
	void UpdatePlayingState(Game& game, float timeDelta);
	void ShutdownPlayingState(Game& game);

	void InitGameOverState(Game& game);
	void UpdateGameOverState(Game& game, float timeDelta);
	void ShutdownGameOverState(Game& game);
}

