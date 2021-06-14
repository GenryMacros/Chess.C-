#pragma once
#include "Piece.h"
namespace playPieces {
	class King : public Piece {
	public:
		King(bool isBlack, sf::Vector2u home);
		void SelectTiles(sf::Vector2u posIn_field, std::list<Tile*>& selectArr, TilesHolder& holder) override;
	private:
		void selectTile(int ymod, int xmod, std::list<Tile*>& selectArr, sf::Vector2u& posIn_field, TilesHolder& holder);
	};
}