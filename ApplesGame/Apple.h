#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
    struct Apple
    {
        Position2D applePostion;
        sf::CircleShape applesShape;
    };

    void InitApples(Apple& apple);
}

