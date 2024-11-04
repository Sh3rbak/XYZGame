#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Platform.h"
#include "Ball.h"
#include "GameStateData.h"

namespace ArkanoidGame
{
	class Game;

	class GameStatePlayingData : public GameStateData
	{
	public:
		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;

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
