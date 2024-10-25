#pragma once
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		ExitDialog,
		Records,
	};

	class GameState
	{
	public:
		GameState() = default;
		GameState(GameStateType type, bool isExclusivelyVisible);
		GameState(GameState&& state) noexcept :
			type(std::move(state.type)),
			isExclusivelyVisible(std::move(state.isExclusivelyVisible))
		{
			data = state.data;
			state.data = nullptr;
		}

		GameState& operator=(GameState&& state) noexcept
		{
			type = state.type;
			data = state.data;
			isExclusivelyVisible = state.isExclusivelyVisible;
			state.data = nullptr;

			return *this;
		}

		~GameState();

		GameStateType GetType() const { return type; };
		bool IsExclusivelyVisible() const { return isExclusivelyVisible; };

		void HandleWindowEvent(sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);

	private:
		GameStateType type = GameStateType::None;
		void* data = nullptr;
		bool isExclusivelyVisible = false;
	};
}

