#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "UIGame.h"

namespace ApplesGame
{
	struct Game
	{
		Rectangle screenRect;

		Player player;
		Apple apples[NUM_APPLES];
		Rock rocks[NUM_ROCKS];

		//Global game data
		float gameFinishTime = 0;
		bool isGameFinished = false;
		int numEatenApples = 0;

		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture rockTexture;

		sf::SoundBuffer deadPlayerBuf;
		sf::Sound deadPlayerSound;
		sf::SoundBuffer eatAppleBuf;
		sf::Sound eatAppleSound;

		UIGame uiGame;
		sf::Font font;
	};

	void InitGame(Game& game);
	void UpdateGame(Game& game, float deltaTime);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void DeinializeGame(Game& game);

	void RestartGame(Game& game);

	void StartPlayingState(Game& game);
	void UpdatePlayingState(Game& game, float deltaTime);

	void StartGameoverState(Game& game);
	void UpdateGameoverState(Game& game, float deltaTime);


}

