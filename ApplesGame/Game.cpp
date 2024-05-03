#include "Game.h"
#include <string>
#include <cassert>

namespace ApplesGame
{
    void InitSound(sf::SoundBuffer& soundBuf, sf::Sound& sound, const std::string& path)
    {
        assert(soundBuf.loadFromFile(path));
        sound.setBuffer(soundBuf);
        sound.setVolume(50.f);
    }

    void InitGame(Game& game)
    {
        assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
        assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
        assert(game.rockTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));

        InitSound(game.deadPlayerBuf, game.deadPlayerSound, RESOURCES_PATH + "\\Death.wav");
        InitSound(game.eatAppleBuf, game.eatAppleSound, RESOURCES_PATH + "\\AppleEat.wav");

        assert(game.font.loadFromFile(RESOURCES_PATH + "\\Fonts\\Roboto-Bold.ttf"));
        InitUI(game.UI, game.font);
        InitMenu(game.menu, game.font);
		InitExitDialog(game.exitDialog, game.font);

        game.gameStateStack.push_back(GameState::Playing);

        PushGameState(game, GameState::Menu);
    }

    void RestartGame(Game& game)
    {
        SwitchGameState(game, GameState::Playing);
    }

    void PushGameState(Game& game, GameState state)
    {
        GameState oldState = GameState::None;
        if (game.gameStateStack.size() > 0)
        {
            oldState = game.gameStateStack.back();
        }

        SwitchGameStateInternal(game, oldState, state);
        game.gameStateStack.push_back(state);
    }

	void HandleWindowEvents(Game& game, sf::RenderWindow& window)
	{
		sf::Event event;
		window.setKeyRepeatEnabled(false);
		while (window.pollEvent(event))
		{
			// Close window if close button or Escape key pressed
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if ((GetCurrentGameState(game) == GameState::Playing) && (event.key.code == sf::Keyboard::Escape))
			{
				SwitchGameState(game, GameState::Menu);
			} 
			else if ((GetCurrentGameState(game) == GameState::Menu) && (event.type == sf::Event::KeyPressed))
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					RestartGame(game);
				}
				else if (event.key.code == sf::Keyboard::Num1)
				{
					game.options = (GameOptions)((std::uint8_t)game.options ^ (std::uint8_t)GameOptions::infiniteApples);
				}
				else if (event.key.code == sf::Keyboard::Num2)
				{
					game.options = (GameOptions)((std::uint8_t)game.options ^ (std::uint8_t)GameOptions::accelerationSpeed);
				}
				else if (event.key.code == sf::Keyboard::Escape)
				{
					PushGameState(game, GameState::ExitDialog);
				}
			}
			else if ((GetCurrentGameState(game) == GameState::ExitDialog) && (event.type == sf::Event::KeyPressed))
			{
				if ((event.key.code == sf::Keyboard::Escape) || (event.key.code == sf::Keyboard::Num1))
				{
					PopGameState(game);	
				} 
				else if (event.key.code == sf::Keyboard::Num2)
				{
					window.close();
				}
			}
		}
	}

	void UpdateGame(Game& game, float timeDelta)
	{
		GameState gameState = game.gameStateStack.back();
		switch (gameState)
		{
		case GameState::Playing:
			UpdatePlayingState(game, timeDelta);
			break;
		case GameState::GameOver:
			UpdateGameOverState(game, timeDelta);
			break;
		case GameState::Menu:
			UpdateMenu(game.menu, game);
			break;
		default:
			break;
		}

		SetScoreInUI(game.UI, game.numEatenApples);
		UpdateUI(game.UI, timeDelta);
	}

	void PopGameState(Game& game)
	{
		GameState oldState = GameState::None;
		if (game.gameStateStack.size() > 0)
		{
			oldState = game.gameStateStack.back();
		}

		game.gameStateStack.pop_back();
		GameState state = GameState::None;
		if (game.gameStateStack.size() > 0)
		{
			state = game.gameStateStack.back();
		}

		SwitchGameStateInternal(game, oldState, state);
	}

	void SwitchGameState(Game& game, GameState newState)
	{
		if (game.gameStateStack.size() > 0)
		{
			GameState oldState = game.gameStateStack.back();
			game.gameStateStack.pop_back();
			game.gameStateStack.push_back(newState);
			SwitchGameStateInternal(game, oldState, newState);
		}
		else
		{
			PushGameState(game, newState);
		}
	}

	void SwitchGameStateInternal(Game& game, GameState oldState, GameState newState)
	{
		switch (oldState)
		{
		case GameState::Playing:
		{
			ShutdownPlayingState(game);
			break;
		}
		case GameState::GameOver:
		{
			ShutdownGameOverState(game);
			break;
		}
		}

		switch (newState)
		{
		case GameState::Playing:
			InitPlayingState(game);
			break;
		case GameState::GameOver:
			InitGameOverState(game);
			break;
		default:
			break;
		}
	}

	GameState GetCurrentGameState(const Game& game)
	{
		if (game.gameStateStack.size() > 0)
		{
			return game.gameStateStack.back();
		}
		else
		{
			return GameState::None;
		}
	}

	void HandleInput(Game& game)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			game.player.direction = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			game.player.direction = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			game.player.direction = PlayerDirection::Down;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			game.player.direction = PlayerDirection::Left;
		}
	}

	void InitPlayingState(Game& game)
	{
		game.apples.clear();

		// Init player
		InitPlayer(game.player, game.playerTexture);
		// Init apples
		int numApples = MIN_NUM_APPLES + rand() % (MAX_NUM_APPLES + 1 - MIN_NUM_APPLES);
		game.apples.resize(numApples);
		for (Apple& apple : game.apples)
		{
			InitApple(apple, game.appleTexture);
			ResetAppleState(apple);
		}
		game.rocks.resize(NUM_ROCKS);
		for (Rock& rock : game.rocks)
		{
			InitRock(rock, game.rockTexture);
			ResetRockState(rock);
		}

		// Init game state
		game.numEatenApples = 0;
	}

	void UpdatePlayingState(Game& game, float timeDelta)
	{
		HandleInput(game);

		// Update player
		UpdatePlayer(game.player, timeDelta);

		for (Apple& apple : game.apples)
		{
			if (DoShapesCollide(GetPlayerCollider(game.player), GetAppleCollider(apple)) && !IsAppleEaten(apple))
			{
				if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::infiniteApples)
				{
					// Move apple to a new random position
					ResetAppleState(apple);
				}
				else
				{
					// Mark apple as eaten
					MarkAppleAsEaten(apple);
				}

				// Increase eaten apples counter
				game.numEatenApples++;
				// Increase player speed
				if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::accelerationSpeed)
				{
					game.player.speed += ACCELERATION;
				}
			}
		}

		for (Rock& rock : game.rocks)
		{
			if (DoShapesCollide(GetRockCollider(rock), GetPlayerCollider(game.player)))
			{
				PushGameState(game, GameState::GameOver);
			}
		}

		bool isGameFinished = (game.numEatenApples == game.apples.size())
			&& !((std::uint8_t)game.options & (std::uint8_t)GameOptions::infiniteApples);
		// Check collision with screen border
		if (isGameFinished || HasPlayerCollisionWithScreenBorder(game.player))
		{
			PushGameState(game, GameState::GameOver);
		}
	}

	void ShutdownPlayingState(Game& game)
	{

	}

	void InitGameOverState(Game& game)
	{
		game.gameFinishTime = 0.f;
		if (GetTotalScore(game.UI.leaderBoard) < game.numEatenApples)
		{
			SetTotalScoreInLeaderBoard(game.UI.leaderBoard, game.numEatenApples);
		}
	}

	void UpdateGameOverState(Game& game, float timeDelta)
	{
		game.gameFinishTime += timeDelta;
		if (game.gameFinishTime > PAUSE_TIME)
		{
			PopGameState(game);
		}
	}

	void ShutdownGameOverState(Game& game)
	{

	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		GameState gameState = game.gameStateStack.back();
		switch (gameState)
		{
		case GameState::Menu:
			DrawMenu(game.menu, window);
			break;
		case GameState::ExitDialog:
			DrawExitDialog(game.exitDialog, window);
			break;
		default:
			// Draw player
			DrawPlayer(game.player, window);
			// Draw apples
			for (Apple& apple : game.apples)
			{
				DrawApple(apple, window);
			}
			for (Rock& rock : game.rocks)
			{
				DrawRock(rock, window);
			}
			GameState state = game.gameStateStack.back();
			bool isGameOver = state == GameState::GameOver;
			DrawUI(game.UI, window, isGameOver);
			break;
		}
	}

	void ShutdownGame(Game& game)
	{
		while (game.gameStateStack.size() > 0)
		{
			PopGameState(game);
		}
	}
}
