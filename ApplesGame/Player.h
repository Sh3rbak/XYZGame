#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
    enum class PlayerDirection
    {
        Right = 0,
        Up,
        Left,
        Down
    };

    struct Player
    {
        Position2D playerPostion;
        float playerSpeed = INITIAL_SPEED;
        PlayerDirection playerDirection = PlayerDirection::Right;
        sf::Sprite sprite;
    };

    void InitPlayer(Player& player, sf::Texture& texture);
    void UpdatePlayer(Player& player, const float deltaTime);
    void DrawPlayer(Player& player, sf::RenderWindow& window);
}