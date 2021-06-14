#include "TilesHolder.h"

	Tile* TilesHolder::getTile(sf::Vector2u coords) {
		if ((coords.x >= _matrixXsize || coords.x < 0) || (coords.y >= _matrixYsize || coords.y < 0))
			return nullptr;
		return &_matrix[coords.y][coords.x];
	}
	void TilesHolder::AddRow(int elemsInRow) {
		_matrix.push_back(std::vector<Tile>(elemsInRow));
	}
	bool TilesHolder::IsTileContainsGameObject(sf::Vector2u gameCoords) {
		return _matrix[gameCoords.y][gameCoords.x].IsContainingGameObject();
	}
	std::vector<std::vector<Tile>>::iterator TilesHolder::lastRow() {
		return std::prev(_matrix.end());
	}

	TilesHolder& TilesHolder::setXsize(size_t x) {
		_matrixXsize = x;
		return *this;
	}

	TilesHolder& TilesHolder::setYsize(size_t y) {
		_matrixYsize = y;
		return *this;
	}

	size_t TilesHolder::getXsize() {
		return _matrixXsize;
	}

	size_t TilesHolder::getYsize() {
		return _matrixYsize;
	}

	void TilesHolder::Draw(sf::RenderWindow& win) {
		for (auto& row : _matrix) {
			for (auto& tile : row)
				tile.Draw(win);
		}
	}