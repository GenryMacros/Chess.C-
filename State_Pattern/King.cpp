#include "King.h"

namespace playPieces {
	King::King(bool isBlack, sf::Vector2u home) : Piece(isBlack, home) {
		if (isBlack) {
			im.loadFromFile(bKing_Path);
			tex.loadFromImage(im);
			sp.setTexture(tex);
		}
		else {
			im.loadFromFile(wKing_Path);
			tex.loadFromImage(im);
			sp.setTexture(tex);
		}
	}
	void King::SelectTiles(sf::Vector2u posIn_field, std::list<Tile*>& selectArr, TilesHolder& holder)  {
		Tile* curTile = holder.getTile(sf::Vector2u(posIn_field.x, posIn_field.y));
		selectArr.push_back(curTile);
		selectTile(static_cast<int>(YMovement::Up), static_cast<int>(XMovement::Right), selectArr, posIn_field, holder);
		selectTile(static_cast<int>(YMovement::Up), static_cast<int>(XMovement::Left), selectArr, posIn_field, holder);
		selectTile(static_cast<int>(YMovement::Up), 0, selectArr, posIn_field, holder);
		selectTile(static_cast<int>(YMovement::Down), 0, selectArr, posIn_field, holder);
		selectTile(0, static_cast<int>(XMovement::Right), selectArr, posIn_field, holder);
		selectTile(0, static_cast<int>(XMovement::Left), selectArr, posIn_field, holder);
		selectTile(static_cast<int>(YMovement::Down), static_cast<int>(XMovement::Right), selectArr, posIn_field, holder);
		selectTile(static_cast<int>(YMovement::Down), static_cast<int>(XMovement::Left), selectArr, posIn_field, holder);
	}
	void King::selectTile(int ymod, int xmod, std::list<Tile*>& selectArr, sf::Vector2u& posIn_field, TilesHolder& holder) {
		Tile* kingTile = holder.getTile(sf::Vector2u(posIn_field.x, posIn_field.y));
		Piece* king = dynamic_cast<Piece*>(kingTile->GetGameObject());
		size_t x = posIn_field.x + xmod;
		size_t y = posIn_field.y + ymod;
		if (auto tile = holder.getTile({ x,y }); tile) {
			if (tile->IsContainingGameObject() &&
				dynamic_cast<Piece*>(tile->GetGameObject())->isBlack() == king->isBlack())
				return;
			selectArr.push_back(tile);
		}
	}
}