#include "Apple.h"

namespace ApplesGame
{
    void InitApples(Apple& apple)
    {
        apple.applePostion = GetRandomPostionInScreen(SCREEN_WIGHT, SCREEN_HEIGHT);

        apple.applesShape.setRadius(APPLE_SIZE / 2.f);
        apple.applesShape.setFillColor(sf::Color::Green);
        apple.applesShape.setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
        apple.applesShape.setPosition(apple.applePostion.x, apple.applePostion.y);
    }
}
