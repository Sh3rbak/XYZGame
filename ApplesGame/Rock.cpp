#include "Rock.h"

namespace ApplesGame
{
    void InitRocks(Rock& rock)
    {
        rock.rockPosition = GetRandomPostionInScreen(SCREEN_WIGHT, SCREEN_HEIGHT);

        rock.rocksShape.setRadius(ROCK_SIZE / 2.f);
        rock.rocksShape.setFillColor(sf::Color::Magenta);
        rock.rocksShape.setOrigin(ROCK_SIZE / 2.f, ROCK_SIZE / 2.f);
        rock.rocksShape.setPosition(rock.rockPosition.x, rock.rockPosition.y);
    }
}
