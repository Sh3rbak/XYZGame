#include "LeaderBoard.h"

namespace ApplesGame
{
	bool operator<(const MumberTopList& left, const MumberTopList& right)
	{
		return left.score > right.score;
	}
	void InitLeaderBoard(LeaderBoard& leaderBoard, const sf::Font& font)
	{
		sf::String names[] = { "Nick", "Ron", "Anna", "Rob", "Liza", "Sara", "Joy", "Eve", "Lea", "Zoe", "Kay", "Ray" };
		leaderBoard.players = new MumberTopList[leaderBoard.numPlayers];

		for (int i = 0; i < leaderBoard.numPlayers; ++i)
		{
			leaderBoard.players[i].score = GetRandomValue(5, 10);
		}
		for (auto prt = leaderBoard.players; prt < leaderBoard.players + leaderBoard.numPlayers; ++prt )
		{
			int randNameIndex = GetRandomValue(0, 11);
			prt->name = names[randNameIndex];
		}
		leaderBoard.players[leaderBoard.numPlayers - 1] = {leaderBoard.playerName, 0};
		std::sort(leaderBoard.players, leaderBoard.players + leaderBoard.numPlayers);

		InitText(leaderBoard.firstText, font, leaderBoard.players->name + "\t" + std::to_string(leaderBoard.players->score),
			25, sf::Color::White, { SCREEN_WIDHT / 2, SCREEN_HEIGHT * 0.7f });
		InitText(leaderBoard.secondText, font, leaderBoard.players[1].name + "\t" + std::to_string(leaderBoard.players[1].score),
			25, sf::Color::White, {SCREEN_WIDHT / 2, SCREEN_HEIGHT * 0.75f});
		InitText(leaderBoard.thirdText, font, leaderBoard.players[2].name + "\t" + std::to_string(leaderBoard.players[2].score),
			25, sf::Color::White, { SCREEN_WIDHT / 2, SCREEN_HEIGHT * 0.8f });
		InitText(leaderBoard.fourthText, font, leaderBoard.players[3].name + "\t" + std::to_string(leaderBoard.players[3].score),
			25, sf::Color::White, {SCREEN_WIDHT / 2, SCREEN_HEIGHT * 0.85f});
		InitText(leaderBoard.fifthText, font, leaderBoard.players[4].name + "\t" + std::to_string(leaderBoard.players[4].score),
			25, sf::Color::White, { SCREEN_WIDHT / 2, SCREEN_HEIGHT * 0.9f });
	}
	void UpdateLeaderBoard(LeaderBoard& leaderBoard)
	{
		for (auto prt = leaderBoard.players; prt < leaderBoard.players + leaderBoard.numPlayers; ++prt)
		{
			if (prt->name == leaderBoard.playerName)
			{
				prt->score = leaderBoard.totalScore;
			}
		}
		std::sort(leaderBoard.players, leaderBoard.players + leaderBoard.numPlayers);

		UpdateText(leaderBoard.firstText, leaderBoard.players->name + "\t" + std::to_string(leaderBoard.players->score));
		UpdateText(leaderBoard.secondText, leaderBoard.players[1].name + "\t" + std::to_string(leaderBoard.players[1].score));
		UpdateText(leaderBoard.thirdText, leaderBoard.players[2].name + "\t" + std::to_string(leaderBoard.players[2].score));
		UpdateText(leaderBoard.fourthText, leaderBoard.players[3].name + "\t" + std::to_string(leaderBoard.players[3].score));
		UpdateText(leaderBoard.fifthText, leaderBoard.players[4].name + "\t" + std::to_string(leaderBoard.players[4].score));
	}
	void DrawLeaderBoard(LeaderBoard& leaderBoard, sf::RenderWindow& window)
	{
		window.draw(leaderBoard.firstText);
		window.draw(leaderBoard.secondText);
		window.draw(leaderBoard.thirdText);
		window.draw(leaderBoard.fourthText);
		window.draw(leaderBoard.fifthText);
	}
}