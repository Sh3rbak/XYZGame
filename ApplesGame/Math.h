#pragma once

namespace sf
{
    class Sprite;
}

namespace ApplesGame
{
    struct Vector2D
    {
        float x = 0;
        float y = 0;
    };

    typedef Vector2D Position2D;

    Position2D GetRandomPostionInScreen(const float screenWidht, const float screenHeight);

    bool isRectanglesCollide(Position2D rect1Position, Vector2D rect1Size,
        Position2D rect2Position, Vector2D rect2Size);

    bool isCirclesCollide(Position2D circle1Position, const float circle1Radius,
        Position2D circle2Position, const float circle2Radius);

    void SetSpriteSize(sf::Sprite& sprite, const float desiredWidth, const float desiredHeight);
    void SetSpriteRelativeOrigin(sf::Sprite& sprite, const float originX, const float originY);
}

