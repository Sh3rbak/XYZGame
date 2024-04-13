#include "Rock.h"

namespace ApplesGame
{
    void InitRock(Rock& rock, sf::Texture& texture)
    {
        rock.rockPosition = GetRandomPostionInScreen(SCREEN_WIGHT, SCREEN_HEIGHT);

        rock.sprite.setTexture(texture);
        SetSpriteSize(rock.sprite, ROCK_SIZE, ROCK_SIZE);
        SetSpriteRelativeOrigin(rock.sprite, 0.5f, 0.5f);
        rock.sprite.setPosition(rock.rockPosition.x, rock.rockPosition.y);
    }
    void DrawRock(Rock& rock, sf::RenderWindow& window)
    {
        window.draw(rock.sprite);
    }
}
