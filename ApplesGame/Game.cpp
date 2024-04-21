#include "Game.h"
#include <string>
#include <cassert>

namespace ApplesGame
{
    void StartPlayingState(Game& game)
    {
        SetPlayerPosition(game.player, { SCREEN_WIDHT / 2.f, SCREEN_HEIGHT / 2.f });
        SetPlayerSpeed(game.player, INITIAL_SPEED);
        SetPlayerDirection(game.player, PlayerDirection::Right);

        for (Apple* prt = game.apples; prt < game.apples + game.numApples; prt++)
        {
            SetApplePosition(*prt, GetRandomPostionInRectangle(game.screenRect));
            prt->isEaten = false;
        }

        for (int i = 0; i < NUM_ROCKS; ++i)
        {
            SetRockPosition(game.rocks[i], GetRandomPostionInRectangle(game.screenRect));
        }

        game.numEatenApples = 0;
        game.gameFinishTime = 0;
        game.isGameFinished = false;
    }

    void UpdatePlayingState(Game& game, float deltaTime)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            SetPlayerDirection(game.player, PlayerDirection::Right);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            SetPlayerDirection(game.player, PlayerDirection::Up);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            SetPlayerDirection(game.player, PlayerDirection::Left);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            SetPlayerDirection(game.player, PlayerDirection::Down);
        }
        UpdatePlayer(game.player, deltaTime);

        if (HasPlayerCollisionWithScreenBorder(game.player))
        {
            StartGameoverState(game);
        }

        if (game.numEatenApples == game.numApples && !(game.gameMode & GameModeMask::infiniteApples))
        {
            StartGameoverState(game);
        }

        for (Apple* prt = game.apples; prt < game.apples + game.numApples; prt++)
        {
            if (DoShapesCollide(GetPlayerCollider(game.player), GetAppleCollider(*prt)) && prt->isEaten == false)
            {
                if (game.gameMode & GameModeMask::infiniteApples)
                {
                    SetApplePosition(*prt, GetRandomPostionInRectangle(game.screenRect));
                }
                else
                {
                    prt->isEaten = true;
                }
                if (game.gameMode & GameModeMask::accelerationSpeed)
                {
                    SetPlayerSpeed(game.player, GetPlayerSpeed(game.player) + ACCELERATION);
                }
                ++game.numEatenApples;
                game.eatAppleSound.play();
            }
        }
        for (Rock rock : game.rocks)
        {
            if (DoShapesCollide(GetRockCollider(rock), GetPlayerCollider(game.player)))
            {
                StartGameoverState(game);
            }
        }
    }

    void StartGameoverState(Game& game)
    {
        game.isGameFinished = true;
        game.gameFinishTime = 0.f;
        game.deadPlayerSound.play();
    }

    void UpdateGameoverState(Game& game, float deltaTime)
    {
        game.gameFinishTime += deltaTime;
        if (game.gameFinishTime >= PAUSE_TIME)
        {
            StartPlayingState(game);
        }
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

        assert(game.font.loadFromFile(RESOURCES_PATH + "\\Fonts\\Roboto-Bold.ttf"));
        InitUIGame(game.uiGame, game.font);
        InitMenu(game.menu, game.font);

        game.screenRect = { 0.f, 0.f , SCREEN_WIDHT, SCREEN_HEIGHT };

        InitPlayer(game.player, game.playerTexture);
        game.numApples = GetRandomValue(MIN_NUM_APPLES, MAX_NUM_APPLES);
        game.apples = new Apple[game.numApples];
        for (Apple* prt = game.apples; prt < game.apples + game.numApples; prt++)
        {
            InitApple(*prt, game.appleTexture);
        }

        for (int i = 0; i < NUM_ROCKS; ++i)
        {
            InitRock(game.rocks[i], game.rockTexture);
        }

        StartPlayingState(game);
    }

    void UpdateGame(Game& game, float deltaTime)
    {
        if (game.gameState == GameStateMask::game && sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
        {
            game.gameState = GameStateMask::menu;
        }
        if (game.gameState == GameStateMask::menu)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                game.gameState = GameStateMask::game;
                StartPlayingState(game);
            }
        }
        if (game.gameState == GameStateMask::game)
        {
            if (!game.isGameFinished)
            {
                UpdatePlayingState(game, deltaTime);
            }
            else
            {
                UpdateGameoverState(game, deltaTime);
            }
            UpdateUIGame(game.uiGame, game.numEatenApples, game.gameFinishTime);
        }
        else if (game.gameState == GameStateMask::menu)
        {
            UpdateMenu(game.menu, game.gameMode, deltaTime);
        }
    }

    void DrawGame(Game& game, sf::RenderWindow& window)
    {
        if (game.gameState == GameStateMask::game)
        {
            DrawPlayer(game.player, window);
            for (Apple* prt = game.apples; prt < game.apples + game.numApples; prt++)
            {
                if (prt->isEaten == false)
                {
                    DrawApple(*prt, window);
                }
            }
            for (Rock rock : game.rocks)
            {
                DrawRock(rock, window);
            }
            DrawUIGame(game.uiGame, window, game.isGameFinished);
        }
        else if (game.gameState == GameStateMask::menu)
        {
            DrawMenu(game.menu, window);
        }
    }

    void DeinializeGame(Game& game)
    {
        delete[] game.apples;
    }
}
