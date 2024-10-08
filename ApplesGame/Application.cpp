#include "Application.h"
#include <cstdlib>

namespace ApplesGame
{
	Application::Application(const std::string& gameName) :
		window(sf::VideoMode(ApplesGame::SCREEN_WIDTH, ApplesGame::SCREEN_HEGHT), gameName)
	{
		// Init random number generator
		unsigned int seed = (unsigned int)time(nullptr); // Get current time as seed. You can also use any other number to fix randomization
		srand(seed);

		InitGame(game);
	}

	Application::~Application()
	{
		ShutdownGame(game);
	}

	void Application::Run()
	{
		// Init game clock
		sf::Clock game_clock;
		sf::Time lastTime = game_clock.getElapsedTime();

		// Game loop
		while (window.isOpen())
		{
			HandleWindowEvents(game, window);

			if (!window.isOpen())
			{
				break;
			}

			// Calculate time delta
			sf::Time currentTime = game_clock.getElapsedTime();
			float timeDelta = currentTime.asSeconds() - lastTime.asSeconds();
			lastTime = currentTime;
			if (UpdateGame(game, timeDelta))
			{
				// Draw everything here
				// Clear the window first
				window.clear();

				DrawGame(game, window);

				// End the current frame, display window contents on screen
				window.display();
			}
			else
			{
				window.close();
			}
		}
	}
}