#include "Ball.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <cassert>

namespace
{
	std::string TEXTURE_ID = "Ball";
}

namespace ArkanoidGame
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
		sf::Vector2f const position = sprite.getPosition() + timeDelta * BALL_SPEED * direction;
		sprite.setPosition(position);

		if (position.x - BALL_SIZE / 2.f < 0 || position.x + BALL_SIZE / 2.f > SCREEN_WIDTH)
		{
			BounceOffVerticalWall();
		}

		if (position.y - BALL_SIZE / 2.f < 0 || position.y + BALL_SIZE / 2.f > SCREEN_HEGHT)
		{
			BounceOffHorizontalWall();
		}
	}

	void Ball::BounceOffHorizontalWall()
	{
		direction.y *= -1;
	}
	void Ball::BounceOffVerticalWall()
	{
		direction.x *= -1;
	}

	void Ball::BounceOffCorner()
	{
		direction.x *= -1;
		direction.y *= -1;
	}

	bool Ball::ChangeDirectionWhenHit(const GameObject& rectangle)
	{
		sf::FloatRect rectPlatform = rectangle.GetRect();
		if (CheckCollisionWithHorizontalWall(rectPlatform))
		{
			BounceOffHorizontalWall();
			return true;
		} 
		else if (CheckCollisionWithVerticalWall(rectPlatform))
		{
			BounceOffVerticalWall();
			return true;
		}
		else if (CheckCollisionWithCorner(rectPlatform))
		{
			if (IsFarCornerHorizontal(rectPlatform))
			{
				BounceOffHorizontalWall();
			} 
			else if (IsFarCornerVertical(rectPlatform))
			{
				BounceOffVerticalWall();
			}
			else
			{
			   BounceOffCorner();
			}
			return true;
		}
		return false;
	}

	bool Ball::CheckCollisionWithHorizontalWall(const sf::FloatRect& rect) const
	{
		sf::Vector2f const positionBall = sprite.getPosition();

		if (rect.left < positionBall.x && positionBall.x < rect.left + rect.width)
		{
			if (positionBall.y < rect.top)
			{
				return std::fabs(positionBall.y - rect.top) < BALL_SIZE / 2.f;
			}

			return std::fabs(positionBall.y - (rect.top + rect.height)) < BALL_SIZE / 2.f;
		}
		return false;
	}

	bool Ball::CheckCollisionWithVerticalWall(const sf::FloatRect& rect) const
	{
		sf::Vector2f const positionBall = sprite.getPosition();

		if (rect.top < positionBall.y && positionBall.y < rect.top + rect.height)
		{
			if (positionBall.x < rect.left)
			{
				return std::fabs(positionBall.x - rect.left) < BALL_SIZE / 2.f;
			}
			if (positionBall.x > rect.left + rect.width)
			{
				return std::fabs(positionBall.x - (rect.left + rect.width)) < BALL_SIZE / 2.f;
			}
		}
		return false;
	}

	bool Ball::CheckCollisionWithCorner(const sf::FloatRect& rect) const
	{
		auto sqr = [](float delta)
			{
				return delta * delta;
			};

		sf::Vector2f const positionBall = sprite.getPosition();

		if (positionBall.x < rect.left)
		{
			const float deltaX = sqr(positionBall.x - rect.left);
			if (positionBall.y < rect.top)
			{
				const float deltaY = sqr(positionBall.y - rect.top);
				return deltaX + deltaY < sqr(BALL_SIZE / 2.f);
			}

			if (positionBall.y > rect.top)
			{
				const float deltaY = sqr(positionBall.y - (rect.top + rect.height));
				return deltaX + deltaY < sqr(BALL_SIZE / 2.f);
			}
		}

		if (positionBall.x > rect.left + rect.width)
		{
			const float deltaX = sqr(positionBall.x - (rect.left + rect.width));
			if (positionBall.y < rect.top)
			{
				const float deltaY = sqr(positionBall.y - rect.top);
				return deltaX + deltaY < sqr(BALL_SIZE / 2.f);
			}

			if (positionBall.y > rect.top)
			{
				const float deltaY = sqr(positionBall.y - (rect.top + rect.height));
				return deltaX + deltaY < sqr(BALL_SIZE / 2.f);
			}
		}
		return false;
	}

	bool Ball::IsFarCornerHorizontal(const sf::FloatRect& rect) const
	{
		sf::Vector2f const positionBall = sprite.getPosition();
		if (direction.x > 0)
		{
			return std::fabs(positionBall.x - (rect.left + rect.width)) < BALL_SIZE / 2.f;
		}
		else
		{
			return std::fabs(positionBall.x - rect.left ) < BALL_SIZE / 2.f;
		}
	}

	bool Ball::IsFarCornerVertical(const sf::FloatRect& rect) const
	{
		sf::Vector2f const positionBall = sprite.getPosition();
		if (direction.y > 0)
		{
			return std::fabs(positionBall.y - (rect.top + rect.height)) < BALL_SIZE / 2.f;
		}
		else
		{
			return std::fabs(positionBall.y - rect.top) < BALL_SIZE / 2.f;
		}
	}
}