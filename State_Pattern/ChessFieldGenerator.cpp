#include "ChessFieldGenerator.h"

ChessFieldInfo ChessFieldGenerator::PrepareForGame(TilesHolder& holder) {
	int yPos = 0;
	bool isnextWhite = true;
	ArrangeFigures(Team::WHITE, yPos, isnextWhite, holder);
	PaintTilesBetweenTeams(yPos, isnextWhite, holder);
	ArrangeFigures(Team::BLACK, yPos, isnextWhite, holder);
	return returnedParams;
};
	void ChessFieldGenerator::ArrangeFigures(Team spawnBlack, int& yPos, bool& isnextWhite, TilesHolder& holder) {
		switch (spawnBlack) {
		case Team::WHITE:
		{
			std::list<Tile*> retinue = ArrangeRetinue(spawnBlack, yPos, isnextWhite, holder);
			std::list<Tile*> pawns = ArrangePawns(spawnBlack, yPos, isnextWhite, holder);
			returnedParams.whiteTiles.insert(returnedParams.whiteTiles.end(), retinue.begin(), retinue.end());
			returnedParams.whiteTiles.insert(returnedParams.whiteTiles.end(), pawns.begin(), pawns.end());
		}
		break;
		case Team::BLACK:
		{
			std::list<Tile*> pawns = ArrangePawns(spawnBlack, yPos, isnextWhite, holder);
			std::list<Tile*> retinue = ArrangeRetinue(spawnBlack, yPos, isnextWhite, holder);
			returnedParams.blackTiles.insert(returnedParams.blackTiles.end(), retinue.begin(), retinue.end());
			returnedParams.blackTiles.insert(returnedParams.blackTiles.end(), pawns.begin(), pawns.end());
		}
		break;
		default:
			throw std::invalid_argument("Wrong team given");
		}
	}

	void ChessFieldGenerator::PaintTilesBetweenTeams(int& yPos, bool& isNextWhite, TilesHolder& holder) {
		for (int i = 2; i < 6; i++, isNextWhite = !isNextWhite) {
			for (int j = 0; j < 8; j++, isNextWhite = !isNextWhite) {
				Tile* curTile = holder.getTile(sf::Vector2u(j, i));
				curTile->ResetImageWithColor(isNextWhite ? whiteColor : blackColor);
			}
			yPos++;
		}
	}

	std::list<Tile*> ChessFieldGenerator::ArrangePawns(Team spawnBlack, int& yPos, bool& isNextWhite, TilesHolder& holder) {
		int xPos = 0;
		std::list<Tile*> pawnTiles;
		for (int i = 0; i < 8; i++, isNextWhite = !isNextWhite) {
			Tile* curTile = holder.getTile(sf::Vector2u(i, yPos));
			pawnTiles.push_back(curTile);
			curTile->ResetImageWithColor(isNextWhite ? whiteColor : blackColor);
			curTile->PlaceGameObject(std::make_unique<playPieces::Pawn>(static_cast<bool>(spawnBlack), sf::Vector2u(i, yPos)));
		}
		isNextWhite = !isNextWhite;
		yPos++;
		return pawnTiles;
	}

	std::list<Tile*> ChessFieldGenerator::ArrangeRetinue(Team spawnBlack, int& yPos, bool& isNextWhite, TilesHolder& holder) {
		int xPos = 0;
		std::list<Tile*> retinueTiles;
		for (int i = 0; i < _spawnOrder.size(); i++, isNextWhite = !isNextWhite) {
			Tile* curTile = holder.getTile(sf::Vector2u(i, yPos));
			retinueTiles.push_back(curTile);
			curTile->ResetImageWithColor(isNextWhite ? whiteColor : blackColor);
			PutPieceInTile(i, spawnBlack, curTile, sf::Vector2u(i, yPos));
		}
		isNextWhite = !isNextWhite;
		yPos++;
		return retinueTiles;
	}

	void ChessFieldGenerator::PutPieceInTile(int spawnOrderIndex, Team team, Tile* tile, sf::Vector2u pieceGameCoords) {
		switch (_spawnOrder[spawnOrderIndex]) {
		case Castle:
			tile->PlaceGameObject(std::make_unique<playPieces::Castle>(static_cast<bool>(team), pieceGameCoords));
			break;
		case Bishop:
			tile->PlaceGameObject(std::make_unique<playPieces::Bishop>(static_cast<bool>(team), pieceGameCoords));
			break;
		case Horse:
			tile->PlaceGameObject(std::make_unique<playPieces::Horse>(static_cast<bool>(team), pieceGameCoords));
			break;
		case Queen:
			tile->PlaceGameObject(std::make_unique<playPieces::Queen>(static_cast<bool>(team), pieceGameCoords));
			break;
		case King:
			tile->PlaceGameObject(std::make_unique<playPieces::King>(static_cast<bool>(team), pieceGameCoords));
			if (team == Team::WHITE)
				returnedParams.whiteKingPos = pieceGameCoords;
			else
				returnedParams.blackKingPos = pieceGameCoords;
			break;
		}
	}