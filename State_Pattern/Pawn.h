#pragma once
#include "Piece.h"
namespace playPieces {
	class Pawn : public Piece {
	public:
		Pawn(bool isBlack, sf::Vector2u home);
		void SelectTiles(sf::Vector2u posIn_field, std::list<Tile*>& selectArr, TilesHolder& holder) override;
	private:
		void selectForwardTiles(sf::Vector2u posIn_field, std::list<Tile*>& selectArr, TilesHolder& holder);
		void select2ForwardTiles(std::list<Tile*>& selectArr, sf::Vector2u posIn_field, TilesHolder& holder);
		void selectForwardTile(std::list<Tile*>& selectArr, sf::Vector2u posIn_field, TilesHolder& holder);
		void targetRightTileIfEnemyExists(sf::Vector2u posIn_field, std::list<Tile*>& selectArr, TilesHolder& holder);
		void targetLeftTileIfEnemyExists(sf::Vector2u posIn_field, std::list<Tile*>& selectArr, TilesHolder& holder);
	};
}