#include "Bishop.h"
namespace playPieces {

	Bishop::Bishop(bool isBlack, sf::Vector2u home) : Piece(isBlack, home) {
		if (isBlack) {
			im.loadFromFile(bBishop_Path);
			tex.loadFromImage(im);
			sp.setTexture(tex);
		}
		else {
			im.loadFromFile(wBishop_Path);
			tex.loadFromImage(im);
			sp.setTexture(tex);
		}
	}
	void Bishop::SelectTiles(sf::Vector2u posIn_field, std::list<Tile*>& selectArr, TilesHolder& holder)  {
		Tile* curTile = holder.getTile(sf::Vector2u(posIn_field.x, posIn_field.y));
		selectArr.push_back(curTile);
		Select(static_cast<int>(YMovement::Up), static_cast<int>(XMovement::Right), selectArr, posIn_field, holder);
		Select(static_cast<int>(YMovement::Up), static_cast<int>(XMovement::Left), selectArr, posIn_field, holder);
		Select(static_cast<int>(YMovement::Down), static_cast<int>(XMovement::Right), selectArr, posIn_field, holder);
		Select(static_cast<int>(YMovement::Down), static_cast<int>(XMovement::Left), selectArr, posIn_field, holder);
	}

	void Bishop::Select(int ymod, int xmod, std::list<Tile*>& selectArr, sf::Vector2u& posIn_field, TilesHolder& holder) {
		Tile* bishopTile = holder.getTile(sf::Vector2u(posIn_field.x, posIn_field.y));
		Piece* bishop = dynamic_cast<Piece*>(bishopTile->GetGameObject());
		int x = posIn_field.x + xmod;
		int y = posIn_field.y + ymod;

		while (holder.getTile(sf::Vector2u(x, y))) {

			if (Tile* tile = holder.getTile(sf::Vector2u(x, y));
				holder.IsTileContainsGameObject(sf::Vector2u(x, y))) {
				Piece* tileToGo = dynamic_cast<Piece*>(tile->GetGameObject());
				if (bishop->isBlack() == tileToGo->isBlack()) {
					break;
				}
				selectArr.push_back(tile);
				break;
			}
			Tile* curTile = holder.getTile(sf::Vector2u(x, y));
			selectArr.push_back(curTile);
			x += xmod;
			y += ymod;
		}
	}
}