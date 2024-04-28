#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "GameSettings.h"

namespace ApplesGame
{
    struct Rock
    {
        Position2D position;
        sf::Sprite sprite;
    };

    void InitRock(Rock& rock, const sf::Texture& texture);
    void DrawRock(Rock& rock, sf::RenderWindow& window);
    Rectangle GetRockCollider(const Rock& rock);
    void ResetRockState(Rock& rock);
}

