#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

namespace ArcanoidGame
{
	class Ball : public GameObject
	{
	public:
		void Init();
		void Update(float timeDelta);
		void BounceOffHorizontalSide();
		void BounceOffVerticalSide();
		bool CheckCollisionWithRectangle(GameObject& platform);
	private:
		sf::Vector2f direction;
	};	
}

