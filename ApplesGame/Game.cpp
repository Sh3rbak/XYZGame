#include "Game.h"
#include <string>
#include <cassert>

namespace ApplesGame
{
    void RestartGame(Game& game)
    {
        InitPlayer(game.player, game.playerTexture);
        for (int i = 0; i < NUM_APPLES; ++i)
        {
            InitApple(game.apples[i], game.appleTexture);
        }
        for (int i = 0; i < NUM_ROCKS; ++i)
        {
            InitRock(game.rocks[i], game.rockTexture);
        }
        game.numEatenApples = 0;
        game.gameFinishTime = 0;
        game.isGameFinished = false;
    }

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

        RestartGame(game);
    }

    void UpdateGame(Game& game, float deltaTime)
    {
        if (!game.isGameFinished)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                game.player.playerDirection = PlayerDirection::Right;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                game.player.playerDirection = PlayerDirection::Up;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                game.player.playerDirection = PlayerDirection::Left;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                game.player.playerDirection = PlayerDirection::Down;
            }
            UpdatePlayer(game.player, deltaTime);

            if (((game.player.playerPostion.x - PLAYER_SIZE / 2.f) < 0) ||
                ((game.player.playerPostion.y - PLAYER_SIZE / 2.f) < 0) ||
                ((game.player.playerPostion.x + PLAYER_SIZE / 2.f) > SCREEN_WIGHT) ||
                ((game.player.playerPostion.y + PLAYER_SIZE / 2.f) > SCREEN_HEIGHT))
            {
                game.isGameFinished = true;
                game.deadPlayerSound.play();
            }

            for (int i = 0; i < NUM_APPLES; ++i)
            {
                if (isCirclesCollide(game.player.playerPostion, PLAYER_SIZE / 2.f,
                    game.apples[i].applePostion, APPLE_SIZE / 2.f))
                {
                    game.player.playerSpeed += ACCELERATION;
                    ++game.numEatenApples;
                    game.apples[i].applePostion = GetRandomPostionInScreen(SCREEN_WIGHT, SCREEN_HEIGHT);
                    game.apples[i].sprite.setPosition(game.apples[i].applePostion.x, game.apples[i].applePostion.y);
                    game.eatAppleSound.play();
                }
            }
            for (int i = 0; i < NUM_ROCKS; ++i)
            {
                if (isCirclesCollide(game.player.playerPostion, PLAYER_SIZE / 2.f,
                    game.rocks[i].rockPosition, ROCK_SIZE / 2.f))
                {
                    game.isGameFinished = true;
                    game.deadPlayerSound.play();
                }
            }
        }
        else
        {
            game.gameFinishTime += deltaTime;
            if (game.gameFinishTime >= PAUSE_TIME)
            {
                RestartGame(game);
            }
        }
    }

    void DrawGame(Game& game, sf::RenderWindow& window)
    {
        DrawPlayer(game.player, window);
        for (int i = 0; i < NUM_APPLES; ++i)
        {
            DrawApple(game.apples[i], window);
        }
        for (int i = 0; i < NUM_ROCKS; ++i)
        {
            DrawRock(game.rocks[i], window);
        }
    }

    void DeinializeGame(Game& game)
    {

    }
}
