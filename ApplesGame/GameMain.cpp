#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const std::string RESOURSE_PATH = "Resourse/";
const int SCREEN_WIGHT = 1240;
const int SCREEN_HEIGHT = 720;
const float INITIAL_SPEED = 100.f;
const float PLAYER_SIZE = 20.f;
const float ACCELERATION = 10.f;
const int NUM_APPLES = 20;
const float APPLE_SIZE = 20.f;

int main()
{
    int seed = (int)time(nullptr);
    srand(seed);
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

    float appleX[NUM_APPLES];
    float appleY[NUM_APPLES];
    bool isAppleEaten[NUM_APPLES];
    sf::CircleShape applesShape[NUM_APPLES];


    for (int i = 0; i < NUM_APPLES; ++i)
    {
        isAppleEaten[i] = false;
        appleX[i] = APPLE_SIZE + rand() / (float)RAND_MAX * (SCREEN_WIGHT - APPLE_SIZE);
        appleY[i] = APPLE_SIZE + rand() / (float)RAND_MAX * (SCREEN_HEIGHT - APPLE_SIZE);

        applesShape[i].setRadius(APPLE_SIZE / 2.f);
        applesShape[i].setFillColor(sf::Color::Green);
        applesShape[i].setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
        applesShape[i].setPosition(appleX[i], appleY[i]);
    }

    int numEatenApples = 0;

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

        /*for (int i = 0; i < NUM_APPLES; ++i)
        {
            if (!isAppleEaten[i])
            {
                float deltaX = fabs(playerX - appleX[i]);
                float deltaY = fabs(playerY - appleY[i]);
                if (deltaX <= (APPLE_SIZE + PLAYER_SIZE) / 2.f &&
                    deltaY <= (APPLE_SIZE + PLAYER_SIZE) / 2.f)
                {
                    isAppleEaten[i] = true;
                    ++numEatenApples;
                }
            }
        }*/
        for (int i = 0; i < NUM_APPLES; ++i)
        {
            if (!isAppleEaten[i])
            {
                float deltaX = (playerX - appleX[i]) * (playerX - appleX[i]);
                float deltaY = (playerY - appleY[i]) * (playerY - appleY[i]);
                float distance = deltaX + deltaY;
                if (distance <= (APPLE_SIZE + PLAYER_SIZE) * (APPLE_SIZE + PLAYER_SIZE) / 4)
                {
                    isAppleEaten[i] = true;
                    ++numEatenApples;
                }
            }
        }

        if (numEatenApples == NUM_APPLES)
        {
            window.close();
            break;
        }

        window.clear();
        playerShape.setPosition(playerX, playerY);
        window.draw(playerShape);
        for (int i = 0; i < NUM_APPLES; ++i)
        {
            if(!isAppleEaten[i])
            {
                window.draw(applesShape[i]);
            }
        }
        window.display();
    }

    return 0;
}