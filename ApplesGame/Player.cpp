#include "Player.h"

namespace ApplesGame
{
    void InitPlayer(Player& player, const sf::Texture& texture)
    {
        player.position = {
            SCREEN_WIDHT / 2.f,
            SCREEN_HEIGHT / 2.f
        };
        player.speed = INITIAL_SPEED;
        player.direction = PlayerDirection::Right;

        player.sprite.setTexture(texture);
        SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
        SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);
    }

    void SetPlayerPosition(Player& player, const Position2D& position)
    {
        player.position = position;
    }

    void SetPlayerSpeed(Player& player, const float speed)
    {
        player.speed = speed;
    }

    float GetPlayerSpeed(const Player& player)
    {
        return player.speed;
    }

    void SetPlayerDirection(Player& player, const PlayerDirection direction)
    {
        player.direction = direction;
    }

    Circle GetPlayerCollider(const Player& player)
    {
        return { player.position, PLAYER_SIZE / 2.f };
    }

    bool HasPlayerCollisionWithScreenBorder(const Player& player)
    {
        return (((player.position.x - PLAYER_SIZE / 2.f) < 0) ||
               ((player.position.y - PLAYER_SIZE / 2.f) < 0) ||
               ((player.position.x + PLAYER_SIZE / 2.f) > SCREEN_WIDHT) ||
               ((player.position.y + PLAYER_SIZE / 2.f) > SCREEN_HEIGHT));
    }

    void UpdatePlayer(Player& player, const float deltaTime)
    {
        switch (player.direction)
        {
        case PlayerDirection::Right:
        {
            player.position.x += player.speed * deltaTime;
            break;
        }
        case PlayerDirection::Up:
        {
            player.position.y -= player.speed * deltaTime;
            break;
        }
        case PlayerDirection::Left:
        {
            player.position.x -= player.speed * deltaTime;
            break;
        }
        case PlayerDirection::Down:
        {
            player.position.y += player.speed * deltaTime;
            break;
        }
        default:
            break;
        }
    }

    void DrawPlayer(Player& player, sf::RenderWindow& window)
    {
        player.sprite.setPosition(player.position.x, player.position.y);
        window.draw(player.sprite);

        if (player.direction == PlayerDirection::Left)
        {
            SetSpriteSize(player.sprite, -PLAYER_SIZE, PLAYER_SIZE);
            player.sprite.setRotation(0.f);
        }
        else
        {
            SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
            player.sprite.setRotation((float)player.direction * -90.f);
        }
    }
}