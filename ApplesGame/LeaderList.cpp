#include "LeaderList.h"

namespace ApplesGame
{
	bool operator<(const Player& left, const Player& right)
	{
		return left.score < left.score;
	}
	void InitLeaderList(LeaderList& leaderList, const sf::Font& font)
	{
		const int numPlayers = 5;
		sf::String names[] = { "Nick", "Ron", "Anna", "Rob", "Liza", "Sara", "Joy", "Eve", "Lea", "Zoe", "Kay", "Ray" };
		
		int scores[numPlayers]{};
		for (int i = 0; i < numPlayers; ++i)
		{
			scores[i] = GetRandomValue(10, 150);
		}
		leaderList.players = new Player[numPlayers];
		Player* start = leaderList.players;
		/*for (auto prt = leaderList.players; prt < leaderList.players + numPlayers; ++prt )
		{
			int randNameIndex = GetRandomValue(0, 12);
			prt -> name = 
		}*/
	}
	void UpdateLeaderList(LeaderList& leaderList)
	{

	}
	void DrawLeaderList(LeaderList& leaderList, sf::RenderWindow& window)
	{

	}
}