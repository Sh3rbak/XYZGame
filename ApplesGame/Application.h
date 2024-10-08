#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

namespace ApplesGame
{
	class Application
	{
	public:
		Application(const std::string& gameName);
		~Application();

		void Run();

	private:
		Game game;
		sf::RenderWindow window;
	};
}
