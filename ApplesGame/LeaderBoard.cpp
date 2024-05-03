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

		leaderBoard.players.resize(MAX_RECORDS_TABLE_SIZE);
		for (MumberTopList& player : leaderBoard.players)
		{
			player.score = GetRandomValue(5, 10);
			int randNameIndex = GetRandomValue(0, 11);
			player.name = names[randNameIndex];
		}

		leaderBoard.players[4] = {leaderBoard.playerName, 0};
		std::sort(leaderBoard.players.begin(), leaderBoard.players.end());

		InitText(leaderBoard.firstText, font, leaderBoard.players[0].name + "\t" + std::to_string(leaderBoard.players[0].score),
			25, sf::Color::White, { SCREEN_WIDHT / 2, SCREEN_HEIGHT * 0.7f }, { 0.5f , 0.5f });
		InitText(leaderBoard.secondText, font, leaderBoard.players[1].name + "\t" + std::to_string(leaderBoard.players[1].score),
			25, sf::Color::White, {SCREEN_WIDHT / 2, SCREEN_HEIGHT * 0.75f}, { 0.5f , 0.5f });
		InitText(leaderBoard.thirdText, font, leaderBoard.players[2].name + "\t" + std::to_string(leaderBoard.players[2].score),
			25, sf::Color::White, { SCREEN_WIDHT / 2, SCREEN_HEIGHT * 0.8f }, { 0.5f , 0.5f });
		InitText(leaderBoard.fourthText, font, leaderBoard.players[3].name + "\t" + std::to_string(leaderBoard.players[3].score),
			25, sf::Color::White, {SCREEN_WIDHT / 2, SCREEN_HEIGHT * 0.85f}, { 0.5f , 0.5f });
		InitText(leaderBoard.fifthText, font, leaderBoard.players[4].name + "\t" + std::to_string(leaderBoard.players[4].score),
			25, sf::Color::White, { SCREEN_WIDHT / 2, SCREEN_HEIGHT * 0.9f }, { 0.5f , 0.5f });
	}
	void UpdateLeaderBoard(LeaderBoard& leaderBoard)
	{
		for (MumberTopList& player : leaderBoard.players)
		{
			if (player.name == leaderBoard.playerName)
			{
				player.score = leaderBoard.totalScore;
			}
		}
		std::sort(leaderBoard.players.begin(), leaderBoard.players.end());

		UpdateText(leaderBoard.firstText, leaderBoard.players[0].name + "\t" + std::to_string(leaderBoard.players[0].score));
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
	void SetTotalScoreInLeaderBoard(LeaderBoard& leaderBoard, unsigned int totalScore)
	{
		leaderBoard.totalScore = totalScore;
	}
	int GetTotalScore(LeaderBoard& leaderBoard)
	{
		return leaderBoard.totalScore;
	}
}