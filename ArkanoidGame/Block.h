#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

namespace ArkanoidGame
{
	class Block : public GameObject
	{
	public:
		void Init() override;
		void Update(float timeDelta);
		void SetPosition(sf::Vector2f position);
	};
}

