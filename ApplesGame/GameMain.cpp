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
const int NUM_ROCKS = 5;
const float ROCK_SIZE = 20.f;
const float PAUSE_TIME = 3.f;

struct Vector2D
{
    float x = 0;
    float y = 0;
};

enum class PlayerDirection
{
    Right = 0,
    Up,
    Left,
    Down
};

typedef Vector2D Position2D;

Position2D GetRandomPostionInScreen()
{
    Position2D result;
    result.x = APPLE_SIZE + rand() / (float)RAND_MAX * (SCREEN_WIGHT - APPLE_SIZE);
    result.y = APPLE_SIZE + rand() / (float)RAND_MAX * (SCREEN_HEIGHT - APPLE_SIZE);
    return result;
}

bool isRectanglesCollide(Position2D rect1Position, Vector2D rect1Size, 
    Position2D rect2Position, Vector2D rect2Size)
{
    const float deltaX = fabs(rect1Position.x - rect2Position.x);
    const float deltaY = fabs(rect1Position.y - rect2Position.y);
    return (deltaX <= (rect2Size.x + rect1Size.x) / 2.f &&
        deltaY <= (rect2Size.y + rect1Size.y) / 2.f);
}

bool isCirclesCollide(Position2D circle1Position, float circle1Radius,
    Position2D circle2Position, float circle2Radius)
{
    const float deltaX = (circle1Position.x - circle2Position.x) *
        (circle1Position.x - circle2Position.x);
    const float deltaY = (circle1Position.y - circle2Position.y) *
        (circle1Position.y - circle2Position.y);
    const float distance = deltaX + deltaY;
    return (distance <= (circle1Radius + circle2Radius) * (circle1Radius + circle2Radius));
}


struct GameState
{

    //Player data
    Position2D playerPostion;
    float playerSpeed = 0.f;
    PlayerDirection playerDirection = PlayerDirection::Right;
    sf::RectangleShape playerShape;

    //Apples data
    Position2D applePostion[NUM_APPLES];
    sf::CircleShape applesShape[NUM_APPLES];

    //Rocks data
    Position2D rockPosition[NUM_ROCKS];
    sf::CircleShape rocksShape[NUM_ROCKS];
    
    //Global game data
    float gameFinishTime = 0;
    bool isGameFinished = false;
    int numEatenApples = 0;
};

void InitGame(GameState& gameState)
{
    gameState.playerPostion = {
        SCREEN_WIGHT / 2.f,
        SCREEN_HEIGHT / 2.f
    };
    gameState.playerSpeed = INITIAL_SPEED;
    gameState.playerDirection = PlayerDirection::Right;

    gameState.playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
    gameState.playerShape.setFillColor(sf::Color::Yellow);
    gameState.playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
    gameState.playerShape.setPosition(gameState.playerPostion.x, gameState.playerPostion.y);

    for (int i = 0; i < NUM_APPLES; ++i)
    {
        gameState.applePostion[i] = GetRandomPostionInScreen();

        gameState.applesShape[i].setRadius(APPLE_SIZE / 2.f);
        gameState.applesShape[i].setFillColor(sf::Color::Green);
        gameState.applesShape[i].setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
        gameState.applesShape[i].setPosition(gameState.applePostion[i].x, gameState.applePostion[i].y);
    }
    gameState.numEatenApples = 0;

    for (int i = 0; i < NUM_ROCKS; ++i)
    {
        gameState.rockPosition[i] = GetRandomPostionInScreen();

        gameState.rocksShape[i].setRadius(ROCK_SIZE / 2.f);
        gameState.rocksShape[i].setFillColor(sf::Color::Magenta);
        gameState.rocksShape[i].setOrigin(ROCK_SIZE / 2.f, ROCK_SIZE / 2.f);
        gameState.rocksShape[i].setPosition(gameState.rockPosition[i].x, gameState.rockPosition[i].y);
    }

    gameState.gameFinishTime = 0;
    gameState.isGameFinished = false;
}

void UpdateGame(GameState& gameState, float deltaTime)
{
    if (!gameState.isGameFinished)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            gameState.playerDirection = PlayerDirection::Right;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            gameState.playerDirection = PlayerDirection::Up;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            gameState.playerDirection = PlayerDirection::Left;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            gameState.playerDirection = PlayerDirection::Down;
        }

        switch (gameState.playerDirection)
        {
        case PlayerDirection::Right:
        {
            gameState.playerPostion.x += gameState.playerSpeed * deltaTime;
            break;
        }
        case PlayerDirection::Up:
        {
            gameState.playerPostion.y -= gameState.playerSpeed * deltaTime;
            break;
        }
        case PlayerDirection::Left:
        {
            gameState.playerPostion.x -= gameState.playerSpeed * deltaTime;
            break;
        }
        case PlayerDirection::Down:
        {
            gameState.playerPostion.y += gameState.playerSpeed * deltaTime;
            break;
        }
        default:
            break;
        }

        gameState.playerShape.setPosition(gameState.playerPostion.x, gameState.playerPostion.y);

        if (((gameState.playerPostion.x - PLAYER_SIZE / 2.f) < 0) || 
            ((gameState.playerPostion.y - PLAYER_SIZE / 2.f) < 0) ||
            ((gameState.playerPostion.x + PLAYER_SIZE / 2.f) > SCREEN_WIGHT) || 
            ((gameState.playerPostion.y + PLAYER_SIZE / 2.f) > SCREEN_HEIGHT))
        {
            gameState.isGameFinished = true;
        }

        for (int i = 0; i < NUM_APPLES; ++i)
        {
            if (isCirclesCollide(gameState.playerPostion, PLAYER_SIZE / 2.f, 
                gameState.applePostion[i], APPLE_SIZE / 2.f))
            {
                gameState.playerSpeed += ACCELERATION;
                ++gameState.numEatenApples;
                gameState.applePostion[i] = GetRandomPostionInScreen();
                gameState.applesShape[i].setPosition(gameState.applePostion[i].x, gameState.applePostion[i].y);
            }
        }
        for (int i = 0; i < NUM_ROCKS; ++i)
        {
            float deltaX = (gameState.playerPostion.x - gameState.rockPosition[i].x) * 
                (gameState.playerPostion.x - gameState.rockPosition[i].x);
            float deltaY = (gameState.playerPostion.y - gameState.rockPosition[i].y) * 
                (gameState.playerPostion.y - gameState.rockPosition[i].y);
            float distance = deltaX + deltaY;
            if (isCirclesCollide(gameState.playerPostion, PLAYER_SIZE / 2.f,
                gameState.rockPosition[i], ROCK_SIZE / 2.f))
            {
                gameState.isGameFinished = true;
            }
        }
    }
    else
    {
        gameState.gameFinishTime += deltaTime;
        if (gameState.gameFinishTime >= PAUSE_TIME)
        {
            gameState.gameFinishTime = 0;
            gameState.isGameFinished = false;
            // Reset player
            gameState.playerPostion.x = SCREEN_WIGHT / 2.f;
            gameState.playerPostion.y = SCREEN_HEIGHT / 2.f;
            gameState.playerSpeed = INITIAL_SPEED;
            gameState.playerDirection = PlayerDirection::Right;
            // Reset apples
            gameState.numEatenApples = 0;
            for (int i = 0; i < NUM_APPLES; ++i)
            {
                gameState.applePostion[i] = GetRandomPostionInScreen();
                gameState.applesShape[i].setPosition(gameState.applePostion[i].x, gameState.applePostion[i].y);
            }
            // Reset rocks
            for (int i = 0; i < NUM_ROCKS; ++i)
            {
                gameState.rockPosition[i] = GetRandomPostionInScreen();
                gameState.rocksShape[i].setPosition(gameState.rockPosition[i].x, gameState.rockPosition[i].y);
            }
        }
    }
}

void DrawGame(GameState& gameState, sf::RenderWindow& window)
{
    
    window.draw(gameState.playerShape);
    for (int i = 0; i < NUM_APPLES; ++i)
    {
        window.draw(gameState.applesShape[i]);
    }
    for (int i = 0; i < NUM_ROCKS; ++i)
    {
        window.draw(gameState.rocksShape[i]);
    }
}

void DeinializeGame(GameState& gameState)
{

}

int main()
{
    int seed = (int)time(nullptr);
    srand(seed);
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIGHT , SCREEN_HEIGHT), "APPLES GAME!");

    //Game init
    GameState gameState;
    InitGame(gameState);

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
        UpdateGame(gameState, deltaTime);
        window.clear();
        DrawGame(gameState, window);
        window.display();
    }

    DeinializeGame(gameState);

    return 0;
}