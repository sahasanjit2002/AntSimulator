#pragma once
#include "world_grid.hpp"


struct DistanceFieldBuilder
{
	static void computeDistance(WorldGrid& grid)
	{
		for (int32_t x(0); x < grid.width; ++x) {
			for (int32_t y(0); y < grid.height; ++y) {
				WorldCell& cell = grid.get(sf::Vector2i(x, y));
				if (cell.wall) {
					cell.wall_dist = 0.0f;
				}
				else {
					cell.wall_dist = getMinDist(x, y, grid);
				}
			}
		}
	}

	static float getMinDist(int32_t x, int32_t y, WorldGrid& grid)
	{
		const sf::Vector2f cell_pos(x, y);
		const int32_t max_iteration = 4;
		float min_dist = max_iteration;
		for (int32_t dx(-max_iteration); dx <= max_iteration; ++dx) {
			for (int32_t dy(-max_iteration); dy <= max_iteration; ++dy) {
				const WorldCell* cell = grid.getSafe(sf::Vector2i(x + dx, y + dy));
				if (cell) {
					if (cell->wall) {
						const float dist = getLength(sf::Vector2f(dx, dy));
						//min_dist = (min_dist == -1.0f) ? dist : std::min(dist, min_dist);
						if (dist < min_dist) {
							min_dist = dist;
						}
					}
				}
			}
		}
		min_dist = (float(max_iteration) - min_dist) / float(max_iteration);
		return min_dist;
	}
};