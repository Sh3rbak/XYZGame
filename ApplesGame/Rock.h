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
    };

    void InitRocks(Rock& rock);
}

