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
		void BounceOffHorizontalSide();
		void BounceOffVerticalSide();
		bool CheckCollisionWithRectangle(GameObject& platform);
	private:
		sf::Vector2f direction;
	};	
}

