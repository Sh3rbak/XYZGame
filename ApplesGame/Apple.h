#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "GameSettings.h"

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
    void MarkAppleEaten(Apple& apple);
    bool IsAppleEaten(Apple& apple);
    Circle GetAppleCollider(const Apple& apple);
    void ResetAppleState(Apple& apple);
}

