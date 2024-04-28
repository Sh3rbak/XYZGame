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

        for (Apple& apple : game.apples)
        {
            ResetAppleState(apple);
        }

        for (Rock& rock : game.rocks)
        {
            ResetRockState(rock);
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

        if (game.numEatenApples == game.apples.size() && !(game.gameMode & GameModeMask::infiniteApples))
        {
            StartGameoverState(game);
        }

        for (Apple& apple : game.apples)
        {
            if (DoShapesCollide(GetPlayerCollider(game.player), GetAppleCollider(apple)) && !IsAppleEaten(apple))
            {
                if (game.gameMode & GameModeMask::infiniteApples)
                {
                    ResetAppleState(apple);
                }
                else
                {
                    MarkAppleEaten(apple);
                }
                if (game.gameMode & GameModeMask::accelerationSpeed)
                {
                    SetPlayerSpeed(game.player, GetPlayerSpeed(game.player) + ACCELERATION);
                }
                ++game.numEatenApples;
                game.eatAppleSound.play();
            }
        }
        for (Rock& rock : game.rocks)
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

        if (GetTotalScore(game.uiGame.leaderBoard) < game.numEatenApples)
        {
            SetTotalScoreInLeaderBoard(game.uiGame.leaderBoard, game.numEatenApples);
        }
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
        int numApples = GetRandomValue(MIN_NUM_APPLES, MAX_NUM_APPLES);
        game.apples.resize(numApples);
        for (Apple& apple : game.apples)
        {
            InitApple(apple, game.appleTexture);
        }
        game.rocks.resize(NUM_ROCKS);
        for (Rock& rock : game.rocks)
        {
            InitRock(rock, game.rockTexture);
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
            for (Apple& apple : game.apples)
            {
                DrawApple(apple, window);
            }
            for (Rock& rock : game.rocks)
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
        
    }
}
