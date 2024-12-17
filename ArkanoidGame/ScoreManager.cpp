#include "ScoreManager.h"

namespace ArkanoidGame
{
	ScoreManager& ScoreManager::Instance()
	{
		static ScoreManager manager;
		return manager;
	}

	void ScoreManager::AddPoints(int points)
	{
		score += points;
	}

	void ScoreManager::ClearScore()
	{
		score = 0;
	}

	int ScoreManager::GetScore() const
	{
		return score;
	}
}