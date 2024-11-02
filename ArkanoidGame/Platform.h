#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

namespace ArcanoidGame
{
	class Platform : public GameObject
	{
	public:
		void Init();
		void Update(float timeDelta);
	private:
		void Move(float speed);
	};
}

