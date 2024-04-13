#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "Apple.h"
#include "Rock.h"

namespace ApplesGame
{
	struct Game
	{
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
	};

	void RestartGame(Game& game);

	void InitGame(Game& game);

	void UpdateGame(Game& game, float deltaTime);

	void DrawGame(Game& game, sf::RenderWindow& window);

	void DeinializeGame(Game& game);
}

