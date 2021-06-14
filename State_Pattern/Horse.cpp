#include "Horse.h"

namespace playPieces {
	Horse::Horse(bool isBlack, sf::Vector2u home) : Piece(isBlack, home) {
		if (isBlack) {
			im.loadFromFile(bHorse_Path);
			tex.loadFromImage(im);
			sp.setTexture(tex);
		}
		else {
			im.loadFromFile(wHorse_Path);
			tex.loadFromImage(im);
			sp.setTexture(tex);
		}
	}
	void Horse::SelectTiles(sf::Vector2u posIn_field, std::list<Tile*>& selectArr, TilesHolder& holder) {
		Tile* curTile = holder.getTile(sf::Vector2u(posIn_field.x, posIn_field.y));
		selectArr.push_back(curTile);
		selectOnY(horseYRange, selectArr, posIn_field, holder);
		selectOnY(-horseYRange, selectArr, posIn_field, holder);
		selectOnX(horseYRange, selectArr, posIn_field, holder);
		selectOnX(-horseYRange, selectArr, posIn_field, holder);
	}
	void Horse::PaintSelectedTiles(std::list<Tile*>& selectArr, sf::Color selectColor) {
		for (Tile* tile : selectArr)
			tile->SetColor(selectColor);
	}
	void Horse::selectOnY(int mod, std::list<Tile*>& selectArr, sf::Vector2u& posIn_field, TilesHolder& holder) {
		int y = posIn_field.y + mod;

		if (holder.getTile(sf::Vector2u(posIn_field.x, y))) {

			if (auto tile = holder.getTile(sf::Vector2u(posIn_field.x + 1, y)); tile &&
				isEnemy(sf::Vector2i(posIn_field.x, posIn_field.y), sf::Vector2i(posIn_field.x + 1, y), holder)) {
				selectArr.push_back(tile);
			}
			if (auto tile = holder.getTile(sf::Vector2u(posIn_field.x - 1, y)); tile &&
				isEnemy(sf::Vector2i(posIn_field.x, posIn_field.y), sf::Vector2i(posIn_field.x - 1, y), holder)) {
				selectArr.push_back(tile);
			}
		}
	}
	void Horse::selectOnX(int mod, std::list<Tile*>& selectArr, sf::Vector2u& posIn_field, TilesHolder& holder) {
		size_t x = posIn_field.x + mod;
		if (holder.getTile({ x, posIn_field.y }))
		{
			if (auto tile = holder.getTile({ x, posIn_field.y + 1 }); tile &&
				isEnemy(sf::Vector2i(posIn_field.x, posIn_field.y), sf::Vector2i(x, posIn_field.y + 1), holder)) {
				selectArr.push_back(tile);
			}
			if (auto tile = holder.getTile({ x, posIn_field.y - 1 }); tile &&
				isEnemy(sf::Vector2i(posIn_field.x, posIn_field.y), sf::Vector2i(x, posIn_field.y - 1), holder)) {
				selectArr.push_back(tile);
			}
		}
	}
	bool Horse::isEnemy(sf::Vector2i thisPos, sf::Vector2i targetPos, TilesHolder& holder) {
		if (!holder.IsTileContainsGameObject(sf::Vector2u(targetPos.x, targetPos.y)))
			return true;
		Tile* curTile = holder.getTile(sf::Vector2u(thisPos.x, thisPos.y));
		Tile* targetTile = holder.getTile(sf::Vector2u(targetPos.x, targetPos.y));
		Piece* curPiece = dynamic_cast<Piece*>(curTile->GetGameObject());
		Piece* tileToGo = dynamic_cast<Piece*>(targetTile->GetGameObject());
		return !(curPiece->isBlack() ==
			tileToGo->isBlack());
	}
}