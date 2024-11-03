#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Platform.h"
#include "Ball.h"

namespace ArcanoidGame
{
	class Game;

	class GameStatePlayingData
	{
	public:
		void Init();
		void HandleWindowEvent(const sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);

	private:
		// Resources
		sf::Font font;
		sf::SoundBuffer gameOverSoundBuffer;

		// Game data
		std::vector<std::shared_ptr<GameObject>> gameObjects;

		// UI data
		sf::Text inputHintText;

		// Sounds
		sf::Sound gameOverSound;
	};
}
