#include "Platform.h"
#include "GameSettings.h"
#include "Sprite.h"
#include "Ball.h"
#include <cassert>

namespace
{
	const std::string TEXTURE_ID = "Platform";
}

namespace ArcanoidGame
{
	void Platform::Init()
	{
		assert(texture.loadFromFile(TEXTURES_PATH + TEXTURE_ID + ".png"));
		InitSprite(sprite, PLATFORM_WIDTH, PLATFORM_HEGHT, texture);
		sprite.setPosition({ SCREEN_WIDTH / 2.f, SCREEN_HEGHT - PLATFORM_HEGHT });
	}

	void Platform::Update(float timeDelta)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			Move(-SPEED_PLATFORM * timeDelta);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			Move(SPEED_PLATFORM * timeDelta);
		}
	}

	void Platform::Move(float speed)
	{
		sf::Vector2f position = sprite.getPosition();
		position.x += speed;
		if (position.x - PLATFORM_WIDTH / 2.f > 0 && position.x + PLATFORM_WIDTH / 2.f < SCREEN_WIDTH)
		{
			sprite.setPosition(position);
		}
	}
}