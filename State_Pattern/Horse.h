#pragma once
#include "Piece.h"
namespace playPieces {
	class Horse : public Piece {
	private:
		const int horseYRange = 2;
	public:
		Horse(bool isBlack, sf::Vector2u home);
		void SelectTiles(sf::Vector2u posIn_field, std::list<Tile*>& selectArr, TilesHolder& holder) override;
	private:
		void PaintSelectedTiles(std::list<Tile*>& selectArr, sf::Color selectColor);
		void selectOnY(int mod, std::list<Tile*>& selectArr, sf::Vector2u& posIn_field, TilesHolder& holder);
		void selectOnX(int mod, std::list<Tile*>& selectArr, sf::Vector2u& posIn_field, TilesHolder& holder);
		bool isEnemy(sf::Vector2i thisPos, sf::Vector2i targetPos, TilesHolder& holder);
	};
}