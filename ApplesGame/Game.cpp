#include "Game.h"

namespace ApplesGame
{
    void RestartGame(Game& game)
    {
        InitPlayer(game.player);
        for (int i = 0; i < NUM_APPLES; ++i)
        {
            InitApples(game.apples[i]);
        }
        for (int i = 0; i < NUM_ROCKS; ++i)
        {
            InitRocks(game.rocks[i]);
        }
        game.numEatenApples = 0;
        game.gameFinishTime = 0;
        game.isGameFinished = false;
    }

    void InitGame(Game& game)
    {
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

            switch (game.player.playerDirection)
            {
            case PlayerDirection::Right:
            {
                game.player.playerPostion.x += game.player.playerSpeed * deltaTime;
                break;
            }
            case PlayerDirection::Up:
            {
                game.player.playerPostion.y -= game.player.playerSpeed * deltaTime;
                break;
            }
            case PlayerDirection::Left:
            {
                game.player.playerPostion.x -= game.player.playerSpeed * deltaTime;
                break;
            }
            case PlayerDirection::Down:
            {
                game.player.playerPostion.y += game.player.playerSpeed * deltaTime;
                break;
            }
            default:
                break;
            }

            game.player.playerShape.setPosition(game.player.playerPostion.x, game.player.playerPostion.y);

            if (((game.player.playerPostion.x - PLAYER_SIZE / 2.f) < 0) ||
                ((game.player.playerPostion.y - PLAYER_SIZE / 2.f) < 0) ||
                ((game.player.playerPostion.x + PLAYER_SIZE / 2.f) > SCREEN_WIGHT) ||
                ((game.player.playerPostion.y + PLAYER_SIZE / 2.f) > SCREEN_HEIGHT))
            {
                game.isGameFinished = true;
            }

            for (int i = 0; i < NUM_APPLES; ++i)
            {
                if (isCirclesCollide(game.player.playerPostion, PLAYER_SIZE / 2.f,
                    game.apples[i].applePostion, APPLE_SIZE / 2.f))
                {
                    game.player.playerSpeed += ACCELERATION;
                    ++game.numEatenApples;
                    game.apples[i].applePostion = GetRandomPostionInScreen(SCREEN_WIGHT, SCREEN_HEIGHT);
                    game.apples[i].applesShape.setPosition(game.apples[i].applePostion.x, game.apples[i].applePostion.y);
                }
            }
            for (int i = 0; i < NUM_ROCKS; ++i)
            {
                float deltaX = (game.player.playerPostion.x - game.rocks[i].rockPosition.x) *
                    (game.player.playerPostion.x - game.rocks[i].rockPosition.x);
                float deltaY = (game.player.playerPostion.y - game.rocks[i].rockPosition.y) *
                    (game.player.playerPostion.y - game.rocks[i].rockPosition.y);
                float distance = deltaX + deltaY;
                if (isCirclesCollide(game.player.playerPostion, PLAYER_SIZE / 2.f,
                    game.rocks[i].rockPosition, ROCK_SIZE / 2.f))
                {
                    game.isGameFinished = true;
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

        window.draw(game.player.playerShape);
        for (int i = 0; i < NUM_APPLES; ++i)
        {
            window.draw(game.apples[i].applesShape);
        }
        for (int i = 0; i < NUM_ROCKS; ++i)
        {
            window.draw(game.rocks[i].rocksShape);
        }
    }

    void DeinializeGame(Game& game)
    {

    }
}
