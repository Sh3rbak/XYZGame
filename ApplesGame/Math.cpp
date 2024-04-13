#include "Math.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
    Position2D GetRandomPostionInScreen(const float screenWidht, const float screenHeight)
    {
        Position2D result;
        result.x = rand() / (float)RAND_MAX * screenWidht;
        result.y = rand() / (float)RAND_MAX * screenHeight;
        return result;
    }

    bool isRectanglesCollide(Position2D rect1Position, Vector2D rect1Size, Position2D rect2Position, Vector2D rect2Size)
    {
        const float deltaX = (float)fabs(rect1Position.x - rect2Position.x);
        const float deltaY = (float)fabs(rect1Position.y - rect2Position.y);
        return (deltaX <= (rect2Size.x + rect1Size.x) / 2.f &&
            deltaY <= (rect2Size.y + rect1Size.y) / 2.f);
    }

    bool isCirclesCollide(Position2D circle1Position, const float circle1Radius, Position2D circle2Position, const float circle2Radius)
    {
        const float deltaX = (circle1Position.x - circle2Position.x) *
            (circle1Position.x - circle2Position.x);
        const float deltaY = (circle1Position.y - circle2Position.y) *
            (circle1Position.y - circle2Position.y);
        const float distance = deltaX + deltaY;
        return (distance <= (circle1Radius + circle2Radius) * (circle1Radius + circle2Radius));
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
}
