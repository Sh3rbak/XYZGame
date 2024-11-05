#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>
#include <fstream>

namespace
{
	const std::string FONT_ID = "Roboto-Regular";
	const std::string GAMEOVER_SOUND_ID = "Death";
	const std::string SELECTED_LEVEL = "Level3";
}

namespace ArkanoidGame
{
	void GameStatePlayingData::Init()
	{
		// Init game resources (terminate if error)
		assert(font.loadFromFile(FONTS_PATH + FONT_ID + ".ttf"));
		assert(gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + GAMEOVER_SOUND_ID + ".wav"));

		gameObjects.emplace_back(std::make_shared<Platform>());
		gameObjects.emplace_back(std::make_shared<Ball>());

		if (!DeserializeGame())
		{
			positionsBlocks.push_back("-+--+--+-"); // + - block, 
			positionsBlocks.push_back("+---+---+"); // - - empty
			positionsBlocks.push_back("--+-+-+--");
			positionsBlocks.push_back("-+--+--+-");
			positionsBlocks.push_back("--+-+-+--");
		}
		
		const int indexFirstBlock = static_cast<int>(gameObjects.size());
		for (auto&& row : positionsBlocks)
		{
			for (int i = 0; i < row.size(); ++i)
			{
				if (row[i] == '+')
				{
					gameObjects.emplace_back(std::make_shared<Block>());
				}
			}
		}

		for (auto&& object : gameObjects)
		{
			object->Init();
		}

		if (indexFirstBlock < gameObjects.size())
		{
			SetPositionEveryBlocks(indexFirstBlock);
		}

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(24);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Use arrow keys to move, ESC to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		numBrokenBlocks = 0;

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
		for (auto&& object : gameObjects)
		{
			object->Update(timeDelta);
		}

		Platform* platform = (Platform*)gameObjects[0].get();
		Ball* ball = (Ball*)gameObjects[1].get();

		const bool isCollisionWithPlatform = ball->ChangeDirectionWhenHit(*platform);
		
		for (int i = 2; i < gameObjects.size(); ++i)
		{
			Block* block = (Block*)gameObjects[i].get();
			if (ball->ChangeDirectionWhenHit(*block))
			{
				++numBrokenBlocks;
				gameObjects.erase(gameObjects.begin() + i);
			}
		}

		const bool isGameWinning = gameObjects.size() < 3;
		const bool isGameFinished = !isCollisionWithPlatform && ball->GetPosition().y + BALL_SIZE / 2.f > SCREEN_HEGHT;
		if (isGameFinished || isGameWinning)
		{
			gameOverSound.play();

			Game& game = Application::Instance().GetGame();
			game.PushState(GameStateType::GameOver, false);
			game.UpdateRecord(PLAYER_NAME, numBrokenBlocks);
			if (isGameWinning)
			{
				game.SetStatusGameAsWinning(true);
			}
		}
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		for (auto&& object : gameObjects)
		{
			object->Draw(window);
		}

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}

	void GameStatePlayingData::SetPositionEveryBlocks(int indexFirstBlock)
	{
		int index = indexFirstBlock;
		const float verticalSpacing = static_cast<float>(SCREEN_HEGHT) / 2.f / (positionsBlocks.size() - 1);
		for (int row = 0; row < positionsBlocks.size(); ++row)
		{
			const float horizontalSpacing = static_cast<float>(SCREEN_WIDTH - BLOCK_WIDTH) / (positionsBlocks[row].size() - 1);
			for (int column = 0; column < positionsBlocks[row].size(); ++column)
			{
				if (positionsBlocks[row][column] == '+')
				{
					sf::Vector2f posBlock;
					posBlock.x = horizontalSpacing * column + BLOCK_WIDTH / 2.f;
					posBlock.y = verticalSpacing * row + BLOCK_HEGHT / 2.f;
					Block* block = (Block*)gameObjects[index].get();
					block->SetPosition(posBlock);
					++index;
				}
			}
		}
	}

	bool GameStatePlayingData::DeserializeGame()
	{
		std::ifstream file(LEVELS_PATH + SELECTED_LEVEL);
		if (file.is_open())
		{
			std::string rowMap;
			while (file >> rowMap)
			{
				positionsBlocks.push_back(rowMap);
			}
			file.close();
			return true;
		}
		return false;
	}
}
