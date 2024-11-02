#include "Ball.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <cassert>

namespace
{
	std::string TEXTURE_ID = "Ball";
}

namespace ArcanoidGame
{
	void Ball::Init()
	{
		assert(texture.loadFromFile(TEXTURES_PATH + TEXTURE_ID + ".png"));
		InitSprite(sprite, BALL_SIZE, BALL_SIZE, texture);
		sprite.setPosition({ SCREEN_WIDTH / 2.f, SCREEN_HEGHT - PLATFORM_HEGHT - BALL_SIZE});

		const int maxAngle = 135;
		const int minAngle = 45;
		const int degree = rand() % (maxAngle - minAngle) + minAngle;
		const float radians = degree * std::acos(-1.f) / 180.f;
		direction.x = (float)std::cos(radians);
		direction.y = (float)std::sin(radians);
	}

	void Ball::Update(float timeDelta)
	{
		sf::Vector2f const position = sprite.getPosition() + timeDelta * INITIAL_SPEED_BALL * direction;
		sprite.setPosition(position);

		if (position.x - BALL_SIZE / 2.f < 0 || position.x + BALL_SIZE / 2.f > SCREEN_WIDTH)
		{
			BounceOffVerticalSide();
		}

		if (position.y - BALL_SIZE / 2.f < 0 || position.y + BALL_SIZE / 2.f > SCREEN_HEGHT)
		{
			BounceOffHorizontalSide();
		}
	}

	void Ball::BounceOffHorizontalSide()
	{
		direction.y *= -1;
	}
	void Ball::BounceOffVerticalSide()
	{
		direction.x *= -1;
	}

	bool Ball::CheckCollisionWithRectangle(GameObject& platform)
	{
		auto sqr = [](float delta)
			{
				return delta * delta;
			};

		sf::FloatRect const rectPlatform = platform.GetRect();
		sf::Vector2f const positionBall = sprite.getPosition();

		if (positionBall.x < rectPlatform.left)
		{
			const float deltaX = sqr(positionBall.x - rectPlatform.left);
			if (positionBall.y < rectPlatform.top)
			{
				const float deltaY = sqr(positionBall.y - rectPlatform.top);
				return deltaX + deltaY < sqr(BALL_SIZE / 2.f);
			}

			if (positionBall.y > rectPlatform.top)
			{
				const float deltaY = sqr(positionBall.y - rectPlatform.top + rectPlatform.height);
				return deltaX + deltaY < sqr(BALL_SIZE / 2.f);
			}

			return std::fabs(positionBall.x - rectPlatform.left) < sqr(BALL_SIZE / 2.f);
		}

		if (positionBall.x > rectPlatform.left + rectPlatform.width)
		{
			const float deltaX = sqr(positionBall.x - rectPlatform.left + rectPlatform.width);
			if (positionBall.y < rectPlatform.top)
			{
				const float deltaY = sqr(positionBall.y - rectPlatform.top);
				return deltaX + deltaY < sqr(BALL_SIZE / 2.f);
			}

			if (positionBall.y > rectPlatform.top)
			{
				const float deltaY = sqr(positionBall.y - rectPlatform.top + rectPlatform.height);
				return deltaX + deltaY < sqr(BALL_SIZE / 2.f);
			}

			return std::fabs(positionBall.x - rectPlatform.left + rectPlatform.width) < sqr(BALL_SIZE / 2.f);
		}

		if (positionBall.y < rectPlatform.top)
		{
			return std::fabs(positionBall.y - rectPlatform.top) < BALL_SIZE / 2.f;
		}

		return std::fabs(positionBall.y - rectPlatform.top + rectPlatform.height) < BALL_SIZE / 2.f;
	}
}