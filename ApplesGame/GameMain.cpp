#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const std::string RESOURSE_PATH = "Resourse/";
const int SCREEN_WIGHT = 1240;
const int SCREEN_HEIGHT = 720;
const float INITIAL_SPEED = 100.f;
const float PLAYER_SIZE = 20.f;
const float ACCELERATION = 10.f;

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIGHT , SCREEN_HEIGHT), "APPLES GAME!");
    float playerX = SCREEN_WIGHT / 2.f;
    float playerY = SCREEN_HEIGHT / 2.f;
    float playerSpeed = INITIAL_SPEED;
    int playerDirection = 0;

    sf::RectangleShape playerShape;
    playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
    playerShape.setFillColor(sf::Color::Yellow);
    playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
    playerShape.setPosition(playerX, playerY);

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
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            playerDirection = 0;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            playerDirection = 1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            playerDirection = 2;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            playerDirection = 3;
        }

        playerSpeed += ACCELERATION * deltaTime;;

        if (playerDirection == 0)
        {
            playerX += playerSpeed * deltaTime;
        }
        else if (playerDirection == 1)
        {
            playerY -= playerSpeed * deltaTime;
        }
        else if (playerDirection == 2)
        {
            playerX -= playerSpeed * deltaTime;
        }
        else
        {
            playerY += playerSpeed * deltaTime;
        }

        if (((playerX - PLAYER_SIZE/2.f) < 0) || ((playerY - PLAYER_SIZE/2.f) < 0) ||
            ((playerX + PLAYER_SIZE/2.f) > SCREEN_WIGHT) || ((playerY + PLAYER_SIZE/2.f) > SCREEN_HEIGHT))
        {
            window.close();
            break;
        }


        window.clear();
        playerShape.setPosition(playerX, playerY);
        window.draw(playerShape);
        window.display();
    }

    return 0;
}