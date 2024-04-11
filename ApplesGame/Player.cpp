#include "Player.h"

namespace ApplesGame
{
    void InitPlayer(Player& player)
    {
        player.playerPostion = {
            SCREEN_WIGHT / 2.f,
            SCREEN_HEIGHT / 2.f
        };
        player.playerSpeed = INITIAL_SPEED;
        player.playerDirection = PlayerDirection::Right;

        player.playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
        player.playerShape.setFillColor(sf::Color::Yellow);
        player.playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
        player.playerShape.setPosition(player.playerPostion.x, player.playerPostion.y);
    }
}