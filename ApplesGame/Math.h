#pragma once
#include <SFML/Graphics.hpp>

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

    struct Rectangle
    {
        Position2D position;
        Vector2D size;
    };

    struct Circle
    {
        Position2D position;
        float radius;
    };

    bool DoShapesCollide(const Rectangle& rect1, const Rectangle& rect2);
    bool DoShapesCollide(const Circle& circle1, const Circle& circle2);
    bool DoShapesCollide(const Rectangle& rect, const Circle& circle);

    Position2D GetRandomPostionInRectangle(const Rectangle& rect);

    void SetSpriteSize(sf::Sprite& sprite, const float desiredWidth, const float desiredHeight);
    void SetSpriteRelativeOrigin(sf::Sprite& sprite, const float originX, const float originY);
    int GetRandomValue(int minValue, int maxValue);

    sf::Vector2f GetTextOrigin(const sf::Text& text, const Vector2D& relativePosition);
}

