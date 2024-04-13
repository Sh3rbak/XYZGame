#include "Player.h"

namespace ApplesGame
{
    void InitPlayer(Player& player, sf::Texture& texture)
    {
        player.playerPostion = {
            SCREEN_WIGHT / 2.f,
            SCREEN_HEIGHT / 2.f
        };
        player.playerSpeed = INITIAL_SPEED;
        player.playerDirection = PlayerDirection::Right;

        player.sprite.setTexture(texture);
        SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
        SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);
    }

    void UpdatePlayer(Player& player, const float deltaTime)
    {
        switch (player.playerDirection)
        {
        case PlayerDirection::Right:
        {
            player.playerPostion.x += player.playerSpeed * deltaTime;
            break;
        }
        case PlayerDirection::Up:
        {
            player.playerPostion.y -= player.playerSpeed * deltaTime;
            break;
        }
        case PlayerDirection::Left:
        {
            player.playerPostion.x -= player.playerSpeed * deltaTime;
            break;
        }
        case PlayerDirection::Down:
        {
            player.playerPostion.y += player.playerSpeed * deltaTime;
            break;
        }
        default:
            break;
        }
        
    }

    void DrawPlayer(Player& player, sf::RenderWindow& window)
    {
        player.sprite.setPosition(player.playerPostion.x, player.playerPostion.y);
        window.draw(player.sprite);

        if (player.playerDirection == PlayerDirection::Left)
        {
            SetSpriteSize(player.sprite, -PLAYER_SIZE, PLAYER_SIZE);
            player.sprite.setRotation(0.f);
        }
        else
        {
            SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
            player.sprite.setRotation((float)player.playerDirection * -90.f);
        }
    }
}