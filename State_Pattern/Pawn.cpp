#include "Pawn.h"

namespace playPieces {
	Pawn::Pawn(bool isBlack, sf::Vector2u home) : Piece(isBlack, home) {
		if (isBlack) {
			im.loadFromFile(bPawn_Path);
			tex.loadFromImage(im);
			sp.setTexture(tex);
		}
		else {
			im.loadFromFile(wPawn_Path);
			tex.loadFromImage(im);
			sp.setTexture(tex);
		}
	}
	void Pawn::SelectTiles(sf::Vector2u posIn_field, std::list<Tile*>& selectArr, TilesHolder& holder)  {
		Tile* curTile = holder.getTile(sf::Vector2u(posIn_field.x, posIn_field.y));
		selectArr.push_back(curTile);
		selectForwardTiles(posIn_field, selectArr, holder);
		targetRightTileIfEnemyExists(posIn_field, selectArr, holder);
		targetLeftTileIfEnemyExists(posIn_field, selectArr, holder);
	}
	void Pawn::selectForwardTiles(sf::Vector2u posIn_field, std::list<Tile*>& selectArr, TilesHolder& holder) {
		int modifier = _isBlack ? -1 : 1;
		Tile* curTile = holder.getTile({ posIn_field.x, posIn_field.y });
		if (!holder.IsTileContainsGameObject({ posIn_field.x, posIn_field.y + modifier })) {
			if (curTile->GetGameCoords() == _home && !holder.IsTileContainsGameObject({ posIn_field.x , posIn_field.y + 2 * modifier }))
				select2ForwardTiles(selectArr, posIn_field, holder);
			else
				selectForwardTile(selectArr, posIn_field, holder);
		}
	}

	void Pawn::select2ForwardTiles(std::list<Tile*>& selectArr, sf::Vector2u posIn_field, TilesHolder& holder) {
		int modifier = _isBlack ? -1 : 1;
		Tile* forward1 = holder.getTile({ posIn_field.x, posIn_field.y + 1 * modifier });
		Tile* forward2 = holder.getTile({ posIn_field.x, posIn_field.y + 2 * modifier });
		selectArr.push_back(forward1);
		selectArr.push_back(forward2);
	}

	void Pawn::selectForwardTile(std::list<Tile*>& selectArr, sf::Vector2u posIn_field, TilesHolder& holder) {
		int modifier = _isBlack ? -1 : 1;
		auto forward1 = holder.getTile({ posIn_field.x, posIn_field.y + 1 * modifier });
		if (!forward1)
			return;
		selectArr.push_back(forward1);
	}

	void Pawn::targetRightTileIfEnemyExists(sf::Vector2u posIn_field, std::list<Tile*>& selectArr, TilesHolder& holder) {
		int modifier = _isBlack ? -1 : 1;
		if (auto tile = holder.getTile({ posIn_field.x + 1, posIn_field.y + 1 * modifier }); tile &&
			(*tile).IsContainingGameObject() && dynamic_cast<Piece*>(tile->GetGameObject())->isBlack() != isBlack()) {
			selectArr.push_back(tile);
		}
	}
	void Pawn::targetLeftTileIfEnemyExists(sf::Vector2u posIn_field, std::list<Tile*>& selectArr, TilesHolder& holder) {
		int modifier = _isBlack ? -1 : 1;
		if (auto tile = holder.getTile({ posIn_field.x - 1 , posIn_field.y + 1 * modifier }); tile &&
			tile->IsContainingGameObject() && dynamic_cast<Piece*>(tile->GetGameObject())->isBlack() != isBlack()) {
			selectArr.push_back(tile);
		}
	}
}