#include "Block.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <cassert>

namespace
{
	const std::string TEXTURE_ID = "Block";
}

namespace ArkanoidGame
{
	void Block::Init()
	{
		assert(texture.loadFromFile(TEXTURES_PATH + TEXTURE_ID + ".png"));
		InitSprite(sprite, BLOCK_WIDTH, BLOCK_HEGHT, texture);
		const int randColorR = rand() % 200 + 54;
		const int randColorG = rand() % 200 + 54;
		const int randColorB = rand() % 200 + 54;
		sprite.setColor(sf::Color(randColorR, randColorG, randColorB));
	}

	void Block::Update(float timeDelta)
	{
	}

	void Block::SetPosition(sf::Vector2f position)
	{
		position.x = std::clamp(position.x, BLOCK_WIDTH / 2.f, SCREEN_WIDTH - BLOCK_WIDTH / 2.f);
		position.y = std::clamp(position.y, BLOCK_HEGHT / 2.f, SCREEN_HEGHT * 3.f / 2.f);
		sprite.setPosition(position);
	}
}
