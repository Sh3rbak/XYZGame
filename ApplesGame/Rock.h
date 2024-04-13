#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
    struct Rock
    {
        Position2D rockPosition;
        sf::CircleShape rocksShape;
        sf::Sprite sprite;
    };

    void InitRock(Rock& rock, sf::Texture& texture);
    void DrawRock(Rock& rock, sf::RenderWindow& window);
}

