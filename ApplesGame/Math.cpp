#include "Math.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
    bool DoShapesCollide(const Rectangle& rect1, const Rectangle& rect2)
    {
        return rect1.position.x < rect2.position.x + rect2.size.x &&
            rect1.position.x + rect1.size.x > rect2.position.x &&
            rect1.position.y < rect2.position.y + rect2.size.y &&
            rect1.position.y + rect1.size.y > rect2.position.y;
    }

    bool DoShapesCollide(const Circle& circle1, const Circle& circle2)
    {
        const float dx = circle1.position.x - circle2.position.x;
        const float dy = circle1.position.y - circle2.position.y;
        const float distance = sqrt(dx * dx + dy * dy);
        return distance < circle1.radius + circle2.radius;
    }

    bool DoShapesCollide(const Rectangle& rect, const Circle& circle)
    {
        const float dx = circle.position.x - std::max(rect.position.x, std::min(circle.position.x, rect.position.x + rect.size.x));
        const float dy = circle.position.y - std::max(rect.position.y, std::min(circle.position.y, rect.position.y + rect.size.y));
        return (dx * dx + dy * dy) < (circle.radius * circle.radius);
    }
    Position2D GetRandomPostionInRectangle(const Rectangle& rect)
    {
        Position2D result;
        result.x = rand() / (float)RAND_MAX * rect.size.x + rect.position.x;
        result.y = rand() / (float)RAND_MAX * rect.size.y + rect.position.y;
        return result;
    }
        
    void SetSpriteSize(sf::Sprite& sprite, const float desiredWidth, const float desiredHeight)
    {
        sf::FloatRect spriteRect = sprite.getLocalBounds();
        sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
        sprite.setScale(scale);
    }

    void SetSpriteRelativeOrigin(sf::Sprite& sprite, const float originX, const float originY)
    {
        sf::FloatRect spriteRect = sprite.getLocalBounds();
        sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
    }

    int GetRandomValue(int minValue, int maxValue)
    {
        return rand() % (maxValue - minValue + 1) + minValue;
    }

    sf::Vector2f GetTextOrigin(const sf::Text& text, const Vector2D& relativePosition)
    {
        sf::FloatRect textSize = text.getLocalBounds();
        const float x = (textSize.left + textSize.width) * relativePosition.x;
        const float y = (textSize.top + textSize.height) * relativePosition.y;
        return { x, y };
    }
}
