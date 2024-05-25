#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <unordered_set>
#include "GameSettings.h"
#include "Math.h"

namespace ApplesGame
{
	struct Apple
	{
		Position position;
		sf::Sprite sprite;
		bool isEaten = false;

		std::unordered_set<struct ApplesGridCell*> gridCells;

		//std::vector <struct ApplesGridCell*> gridCells;
		/*struct ApplesGridCell* gridCells[4] = { nullptr };
		int numGridCells = 0;*/
	};

	void InitApple(Apple& apple, const sf::Texture& texture);
	void ResetAppleState(Apple& apple);
	void DrawApple(Apple& apple, sf::RenderWindow& window);
	void MarkAppleAsEaten(Apple& apple);

	struct ApplesGridCell
	{
		std::unordered_set<Apple*> apples;
		/*Apple* apples[MAX_APPLES_IN_CELL] = { nullptr };
		int numApplesInCell = 0;*/
		//std::vector <Apple*> apples;
	};

	struct ApplesGrid
	{
		std::unordered_map < int, std::unordered_map<int, ApplesGridCell> > cells;
		//std::vector<std::vector<ApplesGridCell>> cells;
		//ApplesGridCell cells[APPLES_GRID_CELLS_HORIZONTAL][APPLES_GRID_CELLS_VERTICAL];
	};

	void ClearApplesGrid(ApplesGrid& applesGrid);
	void AddAppleToGrid(ApplesGrid& applesGrid, Apple& apple);
	void RemoveAppleFromGrid(ApplesGrid& applesGrid, Apple& apple);
	bool FindPlayerCollisionWithApples(const Vector2D& playerPosition, ApplesGrid& grid, Apple** result, int& numFoundApples); // Result should be a pointer to an array of MAX_APPLES / 4 pointers to apples
}
