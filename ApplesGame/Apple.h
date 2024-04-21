#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
    struct Apple
    {
        Position2D position;
        sf::Sprite sprite;
        bool isEaten = false;
    };

    void InitApple(Apple& apple, const sf::Texture& texture);
    void DrawApple(Apple& apple, sf::RenderWindow& window);
    Circle GetAppleCollider(const Apple& apple);
    void SetApplePosition(Apple& apple, const Position2D& position);
}

