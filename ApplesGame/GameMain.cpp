#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"

int main()
{
    using namespace ApplesGame;
    int seed = (int)time(nullptr);
    srand(seed);
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIGHT , SCREEN_HEIGHT), "APPLES GAME!");

    //Game init
    Game game;
    InitGame(game);

    sf::Clock gameClock;
    float lastTime = gameClock.getElapsedTime().asSeconds();

    while (window.isOpen())
    {
        float currentTime = gameClock.getElapsedTime().asSeconds();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        //Game update
        UpdateGame(game, deltaTime);

        window.clear();
        DrawGame(game, window);
        window.display();
    }

    DeinializeGame(game);

    return 0;
}