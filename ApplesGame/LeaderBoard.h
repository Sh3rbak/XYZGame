#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Math.h"
#include "TextFunctions.h"

namespace ApplesGame
{
	struct MumberTopList
	{
		sf::String name = "";
		int score = 0;
	};
	struct LeaderBoard
	{
		std::vector<MumberTopList> players;
		int totalScore = 0;
		sf::String playerName = "Player";

		sf::Text firstText;
		sf::Text secondText;
		sf::Text thirdText;
		sf::Text fourthText;
		sf::Text fifthText;
	};
	void InitLeaderBoard(LeaderBoard& leaderBoard, const sf::Font& font);
	void UpdateLeaderBoard(LeaderBoard& leaderBoard);
	void DrawLeaderBoard(LeaderBoard& leaderBoard, sf::RenderWindow& window);
	void SetTotalScoreInLeaderBoard(LeaderBoard& leaderBoard, unsigned int totalScore);
	int GetTotalScore(LeaderBoard& leaderBoard);
}

