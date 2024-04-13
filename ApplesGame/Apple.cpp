#include "Apple.h"

namespace ApplesGame
{
    void InitApple(Apple& apple, sf::Texture& texture)
    {
        apple.applePostion = GetRandomPostionInScreen(SCREEN_WIGHT, SCREEN_HEIGHT);

        apple.sprite.setTexture(texture);
        SetSpriteSize(apple.sprite, APPLE_SIZE, APPLE_SIZE);
        SetSpriteRelativeOrigin(apple.sprite, 0.5f, 0.5f);
        apple.sprite.setPosition(apple.applePostion.x, apple.applePostion.y);
    }

    void DrawApple(Apple& apple, sf::RenderWindow& window)
    {
        window.draw(apple.sprite);
    }
}
