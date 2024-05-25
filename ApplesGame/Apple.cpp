#include "Apple.h"
#include "GameSettings.h"

#include <cstdlib>
#include <assert.h>

namespace ApplesGame
{
	void InitApple(Apple& apple, const sf::Texture& texture)
	{
		// Init sprite
		apple.sprite.setTexture(texture);
		apple.sprite.setOrigin(GetItemOrigin(apple.sprite, { 0.5f, 0.5f })); // We need to use texture as origin ignores scale
		apple.sprite.setScale(GetSpriteScale(apple.sprite, { APPLE_SIZE, APPLE_SIZE }));
	}

	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		if (apple.isEaten)
		{
			return;
		}
			
		apple.sprite.setPosition(OurVectorToSf(apple.position));
		window.draw(apple.sprite);
	}

	void MarkAppleAsEaten(Apple& apple)
	{
		apple.isEaten = true;
	}

	void ResetAppleState(Apple& apple)
	{
		// init apple state
		apple.position.x = (float)(rand() % SCREEN_WIDTH);
		apple.position.y = (float)(rand() % SCREEN_HEGHT);
		apple.isEaten = false;
	}

	void ClearApplesGrid(ApplesGrid& applesGrid)
	{
		applesGrid.cells.clear();
	}

	void AddAppleToGrid(ApplesGrid& applesGrid, Apple& apple)
	{
		Vector2D appleCornerTL = apple.position + Vector2D{ -APPLE_SIZE / 2, -APPLE_SIZE / 2 };
		Vector2D appleCornerBR = apple.position + Vector2D{ APPLE_SIZE / 2, APPLE_SIZE / 2 };

		const float cellSizeX = (float)SCREEN_WIDTH / APPLES_GRID_CELLS_HORIZONTAL;
		const float cellSizeY = (float)SCREEN_WIDTH / APPLES_GRID_CELLS_VERTICAL;
		int minCellX = std::max((int)(appleCornerTL.x / cellSizeX), 0);
		int maxCellX = std::min((int)(appleCornerBR.x / cellSizeX), (int)APPLES_GRID_CELLS_HORIZONTAL - 1);
		int minCellY = std::max((int)(appleCornerTL.y / cellSizeY), 0);
		int maxCellY = std::min((int)(appleCornerBR.y / cellSizeY), (int)APPLES_GRID_CELLS_VERTICAL - 1);

		std::unordered_set<ApplesGridCell*> newCells;
		// Add apple to new cells
		for (int cellX = minCellX; cellX <= maxCellX; ++cellX)
		{
			for (int cellY = minCellY; cellY <= maxCellY; ++cellY)
			{
				ApplesGridCell& cell = applesGrid.cells[cellX][cellY];
				cell.apples.insert(&apple);
				newCells.insert(&cell);
				assert(cell.apples.size() <= MAX_APPLES_IN_CELL);
			}
		}

		// Remove apple from old cells
		for (auto oldCell : apple.gridCells)
		{
			for (auto appleInCell : oldCell->apples)
			{
				if (appleInCell != &apple)
				{
					oldCell->apples.erase(&apple);
					apple.gridCells.erase(oldCell);
				}
			}
		}
	}

	void RemoveAppleFromGrid(ApplesGrid& applesGrid, Apple& apple)
	{
		for (auto oldCell : apple.gridCells)
		{
			for (auto appleInCell : oldCell->apples)
			{
				if (appleInCell != &apple)
				{
					oldCell->apples.erase(&apple);
				}
			}
		}
	}

	bool FindPlayerCollisionWithApples(const Vector2D& playerPosition, ApplesGrid& grid, Apple** result, int& numFoundApples)
	{
		Vector2D playerCornerTL = playerPosition + Vector2D{ -PLAYER_SIZE / 2, -PLAYER_SIZE / 2 };
		Vector2D playerCornerBR = playerPosition + Vector2D{ PLAYER_SIZE / 2, PLAYER_SIZE / 2 };

		const float cellSizeX = (float)SCREEN_WIDTH / APPLES_GRID_CELLS_HORIZONTAL;
		const float cellSizeY = (float)SCREEN_WIDTH / APPLES_GRID_CELLS_VERTICAL;
		int minCellX = std::max((int)(playerCornerTL.x / cellSizeX), 0);
		int maxCellX = std::min((int)(playerCornerBR.x / cellSizeX), (int)APPLES_GRID_CELLS_HORIZONTAL - 1);
		int minCellY = std::max((int)(playerCornerTL.y / cellSizeY), 0);
		int maxCellY = std::min((int)(playerCornerBR.y / cellSizeY), (int)APPLES_GRID_CELLS_VERTICAL - 1);

		numFoundApples = 0;
		for (int cellX = minCellX; cellX <= maxCellX; ++cellX)
		{
			for (int cellY = minCellY; cellY <= maxCellY; ++cellY)
			{
				for (const auto apple : grid.cells[cellX][cellY].apples)
				{
					if (!apple->isEaten)
					{
						float dx = playerPosition.x - apple->position.x;
						float dy = playerPosition.y - apple->position.y;
						float distance = sqrt(dx * dx + dy * dy);
						if (distance < (PLAYER_SIZE + APPLE_SIZE) / 2)
						{
							result[numFoundApples] = apple;
							++numFoundApples;
						}
					}
				}
			}
		}

		return numFoundApples > 0;
	}
}
