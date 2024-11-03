#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

namespace ArcanoidGame
{
	class Platform : public GameObject
	{
	public:
		void Init() override;
		void Update(float timeDelta) override;
	private:
		void Move(float speed);
	};
}

