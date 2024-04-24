#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"
#include "TextFunctions.h"

namespace ApplesGame
{
	struct Player
	{
		sf::String name = "";
		int score = 0;
	};
	struct LeaderList
	{
		Player* players = nullptr;
		int scorePlayer = 0;
		sf::String playerName = "Player";

		sf::Text firstText;
		sf::Text secondText;
		sf::Text thirdText;
		sf::Text fourthText;
		sf::Text fifthText;
		sf::Text scoreCurrentText;
	};
	void InitLeaderList(LeaderList& leaderList, const sf::Font& font);
	void UpdateLeaderList(LeaderList& leaderList);
	void DrawLeaderList(LeaderList& leaderList, sf::RenderWindow& window);
}

