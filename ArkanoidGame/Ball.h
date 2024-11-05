#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

namespace ArkanoidGame
{
	class Ball : public GameObject
	{
	public:
		void Init() override;
		void Update(float timeDelta) override;
		void BounceOffHorizontalWall();
		void BounceOffVerticalWall();
		void BounceOffCorner();
		bool ChangeDirectionWhenHit(const GameObject& rectangle);
	private:
		bool CheckCollisionWithHorizontalWall(const sf::FloatRect& rect) const;
		bool CheckCollisionWithVerticalWall(const sf::FloatRect& rect) const;
		bool CheckCollisionWithCorner(const sf::FloatRect& rect) const;
		bool IsFarCornerHorizontal(const sf::FloatRect& rect) const;
		bool IsFarCornerVertical(const sf::FloatRect& rect) const;
	private:
		sf::Vector2f direction;
	};	
}

