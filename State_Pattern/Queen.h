#pragma once
#include "Piece.h"

namespace playPieces {
	class Queen : public Piece {
	public:
		Queen(bool isBlack, sf::Vector2u home);
		void SelectTiles(sf::Vector2u posIn_field, std::list<Tile*>& selectArr, TilesHolder& holder) override;
	private:
		void selectOnY(int mod, std::list<Tile*>& selectArr, sf::Vector2u& posIn_field, TilesHolder& holder);
		void selectOnX(int mod, std::list<Tile*>& selectArr, sf::Vector2u& posIn_field, TilesHolder& holder);
		void select(int ymod, int xmod, std::list<Tile*>& selectArr, sf::Vector2u& posIn_field, TilesHolder& holder);
	};
}
