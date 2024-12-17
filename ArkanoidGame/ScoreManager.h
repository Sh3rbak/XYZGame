#pragma once
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
	class ScoreManager
	{
	public:
		ScoreManager(const ScoreManager& manager) = delete;
		ScoreManager& operator= (const ScoreManager&) = delete;

		static ScoreManager& Instance();

		void AddPoints(int points);
		void ClearScore();
		int GetScore() const;

	private:
		ScoreManager() : score(0) {};
		~ScoreManager() = default;

	private:
		int score;
	};
}

