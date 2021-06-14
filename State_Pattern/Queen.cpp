#include "Queen.h"

namespace playPieces {
	Queen::Queen(bool isBlack, sf::Vector2u home) : Piece(isBlack, home) {
		if (isBlack) {
			im.loadFromFile(bQueen_Path);
			tex.loadFromImage(im);
			sp.setTexture(tex);
		}
		else {
			im.loadFromFile(wQueen_Path);
			tex.loadFromImage(im);
			sp.setTexture(tex);
		}
	}
	void Queen::SelectTiles(sf::Vector2u posIn_field, std::list<Tile*>& selectArr, TilesHolder& holder) {
		Tile* curTile = holder.getTile(sf::Vector2u(posIn_field.x, posIn_field.y));
		selectArr.push_back(curTile);
		selectOnY(YMovement::Up, selectArr, posIn_field, holder);
		selectOnY(YMovement::Down, selectArr, posIn_field, holder);
		selectOnX(XMovement::Right, selectArr, posIn_field, holder);
		selectOnX(XMovement::Left, selectArr, posIn_field, holder);
		select(static_cast<int>(YMovement::Up), static_cast<int>(XMovement::Right), selectArr, posIn_field, holder);
		select(static_cast<int>(YMovement::Up), static_cast<int>(XMovement::Left), selectArr, posIn_field, holder);
		select(static_cast<int>(YMovement::Down), static_cast<int>(XMovement::Right), selectArr, posIn_field, holder);
		select(static_cast<int>(YMovement::Down), static_cast<int>(XMovement::Left), selectArr, posIn_field, holder);

	}
	void Queen::selectOnY(int mod, std::list<Tile*>& selectArr, sf::Vector2u& posIn_field, TilesHolder& holder) {
		Tile* queenTile = holder.getTile(sf::Vector2u(posIn_field.x, posIn_field.y));
		Piece* queen = dynamic_cast<Piece*>(queenTile->GetGameObject());
		for (int i = posIn_field.y + mod; i >= 0 && i < holder.getYsize(); i += mod) {
			if (Tile* curTile = holder.getTile(sf::Vector2u(posIn_field.x, i));
				holder.IsTileContainsGameObject(sf::Vector2u(posIn_field.x, i))) {
				Piece* tileToGo = dynamic_cast<Piece*>(curTile->GetGameObject());
				if (tileToGo->isBlack() ==
					queen->isBlack())
					break;
				selectArr.push_back(curTile);
				break;
			}
			Tile* curTile = holder.getTile(sf::Vector2u(posIn_field.x, i));
			selectArr.push_back(curTile);
		}
	}
	void Queen::selectOnX(int mod, std::list<Tile*>& selectArr, sf::Vector2u& posIn_field, TilesHolder& holder) {
		Tile* queenTile = holder.getTile(sf::Vector2u(posIn_field.x, posIn_field.y));
		Piece* queen = dynamic_cast<Piece*>(queenTile->GetGameObject());
		for (int i = posIn_field.x + mod; i >= 0 && i < holder.getXsize(); i += mod) {
			if (Tile* curTile = holder.getTile(sf::Vector2u(i, posIn_field.y));
				holder.IsTileContainsGameObject(sf::Vector2u(i, posIn_field.y))) {
				Piece* tileToGo = dynamic_cast<Piece*>(curTile->GetGameObject());
				if (tileToGo->isBlack() ==
					queen->isBlack())
					break;
				selectArr.push_back(curTile);
				break;
			}
			Tile* curTile = holder.getTile(sf::Vector2u(i, posIn_field.y));
			selectArr.push_back(curTile);
		}
	}
	void Queen::select(int ymod, int xmod, std::list<Tile*>& selectArr, sf::Vector2u& posIn_field, TilesHolder& holder) {
		Tile* queenTile = holder.getTile(sf::Vector2u(posIn_field.x, posIn_field.y));
		Piece* queen = dynamic_cast<Piece*>(queenTile->GetGameObject());
		int x = posIn_field.x + xmod;
		int y = posIn_field.y + ymod;

		while (holder.getTile(sf::Vector2u(x, y))) {

			if (auto tile = holder.getTile(sf::Vector2u(x, y));
				holder.IsTileContainsGameObject(sf::Vector2u(x, y))) {
				Piece* tileToGo = dynamic_cast<Piece*>(tile->GetGameObject());
				if (tileToGo->isBlack()
					== queen->isBlack()) {
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