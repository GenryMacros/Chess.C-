#pragma once
#include "Piece.h"
namespace playPieces {
	class Castle : public Piece {
	public:
		Castle(bool isBlack, sf::Vector2u home);
		void SelectTiles(sf::Vector2u posIn_field, std::list<Tile*>& selectArr, TilesHolder& holder) override;
	private:
		void selectOnY(int mod, std::list<Tile*>& selectArr, sf::Vector2u& posIn_field, TilesHolder& holder);
		void selectOnX(int mod, std::list<Tile*>& selectArr, sf::Vector2u& posIn_field, TilesHolder& holder);
	};
}