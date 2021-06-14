#pragma once
class TilesHolder;
#include "SFML/Graphics.hpp"
#include <vector>
#include <memory>
#include "Tile.h"

class TilesHolder {
private:
	size_t _matrixXsize;
	size_t _matrixYsize;
	std::vector<std::vector<Tile>> _matrix;
public:
	void Draw(sf::RenderWindow& win);
	Tile* getTile(sf::Vector2u coords);
	void AddRow(int elemsInRow);
	bool IsTileContainsGameObject(sf::Vector2u gameCoords);
	std::vector<std::vector<Tile>>::iterator lastRow();
	TilesHolder& setXsize(size_t x);
	TilesHolder& setYsize(size_t y);
	size_t getXsize();
	size_t getYsize();
};