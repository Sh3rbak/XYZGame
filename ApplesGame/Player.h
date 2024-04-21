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
        Position2D position;
        float speed = INITIAL_SPEED;
        PlayerDirection direction = PlayerDirection::Right;
        sf::Sprite sprite;
    };

    void SetPlayerPosition(Player& player, const Position2D& position);
    void SetPlayerSpeed(Player& player, const float speed);
    float GetPlayerSpeed(const Player& player);
    Circle GetPlayerCollider(const Player& player);
    bool HasPlayerCollisionWithScreenBorder(const Player& player);
    void SetPlayerDirection(Player& player, const PlayerDirection direction);
    void InitPlayer(Player& player, const sf::Texture& texture);
    void UpdatePlayer(Player& player, const float deltaTime);
    void DrawPlayer(Player& player, sf::RenderWindow& window);
}