#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>

namespace
{
	const std::string FONT_ID = "Roboto-Regular";
	const std::string GAMEOVER_SOUND_ID = "Death";
}

namespace ArcanoidGame
{
	void GameStatePlayingData::Init()
	{	
		// Init game resources (terminate if error)
		assert(font.loadFromFile(FONTS_PATH + FONT_ID + ".ttf"));
		assert(gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + GAMEOVER_SOUND_ID + ".wav"));

		platform.Init();
		ball.Init();

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(24);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Use arrow keys to move, ESC to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		// Init sounds
		gameOverSound.setBuffer(gameOverSoundBuffer);
	}

	void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PushState(GameStateType::ExitDialog, false);
			}
		}
	}

	void GameStatePlayingData::Update(float timeDelta)
	{
		platform.Update(timeDelta);
		ball.Update(timeDelta);

		if (ball.CheckCollisionWithRectangle(platform))
		{
			ball.BounceOffHorizontalSide();
		}

		const bool isGameFinished = ball.GetPosition().y + BALL_SIZE / 2.f > SCREEN_HEGHT;
		if (isGameFinished)
		{
			gameOverSound.play();

			Game& game = Application::Instance().GetGame();
			game.PushState(GameStateType::GameOver, false);
		}
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		platform.Draw(window);
		ball.Draw(window);
		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}
}
