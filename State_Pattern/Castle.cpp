#include "Castle.h"

namespace playPieces {
	Castle::Castle(bool isBlack, sf::Vector2u home) : Piece(isBlack, home) {
		if (isBlack) {
			im.loadFromFile(bCastle_Path);
			tex.loadFromImage(im);
			sp.setTexture(tex);
		}
		else {
			im.loadFromFile(wCastle_Path);
			tex.loadFromImage(im);
			sp.setTexture(tex);
		}
	}
	void Castle::SelectTiles(sf::Vector2u posIn_field, std::list<Tile*>& selectArr, TilesHolder& holder)  {
		Tile* curTile = holder.getTile(sf::Vector2u(posIn_field.x, posIn_field.y));
		selectArr.push_back(curTile);
		selectOnY(YMovement::Up, selectArr, posIn_field, holder);
		selectOnY(YMovement::Down, selectArr, posIn_field, holder);
		selectOnX(XMovement::Right, selectArr, posIn_field, holder);
		selectOnX(XMovement::Left, selectArr, posIn_field, holder);
	}
	void Castle::selectOnY(int mod, std::list<Tile*>& selectArr, sf::Vector2u& posIn_field, TilesHolder& holder) {
		Tile* castleTile = holder.getTile(sf::Vector2u(posIn_field.x, posIn_field.y));
		Piece* castle = dynamic_cast<Piece*>(castleTile->GetGameObject());
		for (int i = posIn_field.y + mod; i >= 0 && i < holder.getYsize(); i += mod) {
			if (Tile* curTile = holder.getTile(sf::Vector2u(posIn_field.x, i));
				holder.IsTileContainsGameObject(sf::Vector2u(posIn_field.x, i))) {
				Piece* tileToGo = dynamic_cast<Piece*>(castleTile->GetGameObject());
				if (tileToGo->isBlack() == castle->isBlack())
					break;
				selectArr.push_back(curTile);
				break;
			}
			Tile* curTile = holder.getTile(sf::Vector2u(posIn_field.x, i));
			selectArr.push_back(curTile);
		}
	}
	void Castle::selectOnX(int mod, std::list<Tile*>& selectArr, sf::Vector2u& posIn_field, TilesHolder& holder) {
		Tile* castleTile = holder.getTile(sf::Vector2u(posIn_field.x, posIn_field.y));
		Piece* castle = dynamic_cast<Piece*>(castleTile->GetGameObject());
		for (int i = posIn_field.x + mod; i >= 0 && i < holder.getXsize(); i += mod) {
			if (Tile* curTile = holder.getTile(sf::Vector2u(i, posIn_field.y));
				holder.IsTileContainsGameObject(sf::Vector2u(i, posIn_field.y))) {
				Piece* tileToGo = dynamic_cast<Piece*>(castleTile->GetGameObject());
				if (tileToGo->isBlack() ==
					castle->isBlack())
					break;
				selectArr.push_back(curTile);
				break;
			}
			Tile* curTile = holder.getTile(sf::Vector2u(i, posIn_field.y));
			selectArr.push_back(curTile);
		}
	}
}