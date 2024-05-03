#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace ApplesGame;

int main()
{
    int seed = (int)time(nullptr);
    srand(seed);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDHT , SCREEN_HEIGHT), "APPLES GAME!");

    //Game init
    ApplesGame::Game* game = new ApplesGame::Game();
    InitGame(*game);

    sf::Clock gameClock;
    float lastTime = gameClock.getElapsedTime().asSeconds();

    while (window.isOpen())
    {
        HandleWindowEvents(*game, window);

        if (!window.isOpen())
        {
            break;
        }

        sf::sleep(sf::milliseconds(16));

        float currentTime = gameClock.getElapsedTime().asSeconds();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        //Game update
        UpdateGame(*game, deltaTime);

        window.clear();
        DrawGame(*game, window);
        window.display();
    }

    ShutdownGame(*game);
    delete game;
    game = nullptr;

    return 0;
}