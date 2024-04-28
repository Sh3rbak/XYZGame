#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameSettings.h"
#include "Math.h"
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "UIGame.h"
#include "Menu.h"

namespace ApplesGame
{
	enum class GameStateMask
	{
		game = 0,
		menu
	};

	enum GameModeMask
	{
		accelerationSpeed = 1 << 0,
		infiniteApples = 1 << 1
	};

	struct Game
	{
		Rectangle screenRect;

		Player player;
		std::vector<Apple> apples;
		std::vector<Rock> rocks;

		float gameFinishTime = 0;
		bool isGameFinished = false;
		int numEatenApples = 0;
		GameStateMask gameState  = GameStateMask::menu;
		int gameMode = 3;

		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture rockTexture;

		sf::SoundBuffer deadPlayerBuf;
		sf::Sound deadPlayerSound;
		sf::SoundBuffer eatAppleBuf;
		sf::Sound eatAppleSound;

		sf::Font font;
		UIGame uiGame;
		Menu menu;
	};

	void InitGame(Game& game);
	void UpdateGame(Game& game, float deltaTime);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void DeinializeGame(Game& game);

	
	void StartPlayingState(Game& game);
	void UpdatePlayingState(Game& game, float deltaTime);

	void StartGameoverState(Game& game);
	void UpdateGameoverState(Game& game, float deltaTime);

}

