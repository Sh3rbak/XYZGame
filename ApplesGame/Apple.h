#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
    struct Apple
    {
        Position2D applePostion;
        sf::Sprite sprite;
    };

    void InitApple(Apple& apple, sf::Texture& texture);
    void DrawApple(Apple& apple, sf::RenderWindow& window);
}

