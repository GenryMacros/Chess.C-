#include "ChessGameRule.h"

ChessGameRule::ChessGameRule() : _players(std::make_unique<HumanPlayer>(sf::Color(100, 100, 100)), std::make_unique<HumanPlayer>(sf::Color(100, 100, 100))) {}
void ChessGameRule::PrepareForGame(TilesHolder& holder) {
	ChessFieldGenerator generator;
	piecesMainInfo = generator.PrepareForGame(holder);
	_players.SetPlayerOneGameObjs(&piecesMainInfo.whiteTiles);
	_players.SetPlayerTwoGameObjs(&piecesMainInfo.blackTiles);
};
std::pair<bool, std::string> ChessGameRule::HandleClick(sf::Vector2i mouseCoords, std::vector<Tile*>& selected, TilesHolder& holder)  {
	sf::Vector2u currentPlayerKing = GetKingPos((Team)_players.GetCurrentPlayer());
	if (!IsPlayerHaveMoves(currentPlayerKing, holder))
		return std::pair<bool, std::string>(true, "");

	std::optional<MoveCoords> moveCoords = _players.MakeTurn(mouseCoords, holder);

	if (!moveCoords.has_value())
		return std::pair<bool, std::string>(false, "");

	if (IsMovePossible(holder, moveCoords.value(), currentPlayerKing)) {
		MakeMove(holder, moveCoords.value(), currentPlayerKing);
		_players.PassTurn();
		return std::pair<bool, std::string>(false, "");
	}
}
bool ChessGameRule::IsPlayerHaveMoves(sf::Vector2u currentKingPos, TilesHolder& holder) {
	std::list<Tile*> controlledByPlayer = *_players.GetCurrentPlayerObjects();
	for (Tile* tile : controlledByPlayer) {
		std::list<Tile*> currentPieceMoves;
		tile->GetGameObject()->SelectTiles(tile->GetGameCoords(), currentPieceMoves, holder);
		currentPieceMoves.erase(currentPieceMoves.begin());
		for (Tile* selected : currentPieceMoves) {
			if (IsMovePossible(holder, MoveCoords{ tile->GetGameCoords(), selected->GetGameCoords() }, currentKingPos))
				return true;
		}
	}
	return false;
}
bool ChessGameRule::IsMovePossible(TilesHolder& holder, MoveCoords coords, sf::Vector2u currentKingPos) {
	Tile* oldTile = holder.getTile(coords.oldPos);
	Tile* newTile = holder.getTile(coords.newPos);
	sf::Vector2u newKingPos = currentKingPos;

	std::unique_ptr<GameObject> replaced = ReplacePieceAndReturnKilled(oldTile, newTile, newKingPos);

	if (!IsPlayerDefeated(holder, newKingPos)) {
		SwapBack(newTile, oldTile, newKingPos, std::move(replaced));
		return true;
	}
	SwapBack(newTile, oldTile, newKingPos, std::move(replaced));
	return false;
}
std::unique_ptr<GameObject> ChessGameRule::ReplacePieceAndReturnKilled(Tile* oldTile, Tile* newTile, sf::Vector2u& currentKingPos) {
	std::unique_ptr<GameObject> replaced = std::move(oldTile->ReplaceGameObj(*newTile));
	if (oldTile->GetGameCoords() == currentKingPos)
		currentKingPos = newTile->GetGameCoords();
	CorrectArraysOfGivenTeam(oldTile, newTile, replaced.get());
	return replaced;
}
void ChessGameRule::SwapBack(Tile* oldTile, Tile* newTile, sf::Vector2u& currentKingPos, std::unique_ptr<GameObject> killed) {
	newTile->PlaceGameObject(std::move(killed));
	newTile->SwapGameObejcts(*oldTile);
	if (oldTile->GetGameCoords() == currentKingPos)
		currentKingPos = newTile->GetGameCoords();
	PlaceKilledBack(oldTile, newTile, oldTile->GetGameObject());
}
bool ChessGameRule::IsPlayerDefeated(TilesHolder& holder, sf::Vector2u currentKingPos) {
	std::list<Tile*> attackedByOpponentTiles = std::move(_players.GetToCurrentEnemyPossibleMoves(holder));

	if (!IsKingAttacked(attackedByOpponentTiles, currentKingPos))
		return false;
	return true;
}
bool ChessGameRule::IsKingAttacked(std::list<Tile*>& tilesUnderAttack, sf::Vector2u currentKingPos) {
	for (Tile* tile : tilesUnderAttack) {
		if (tile->GetGameCoords() == currentKingPos)
			return true;
	}
	return false;
}
void ChessGameRule::MakeMove(TilesHolder& holder, MoveCoords coords, sf::Vector2u currentKingPos) {
	Tile* oldTile = holder.getTile(coords.oldPos);
	Tile* newTile = holder.getTile(coords.newPos);

	std::unique_ptr<GameObject> replaced = std::move(oldTile->ReplaceGameObj(*newTile));

	if (oldTile->GetGameCoords() == currentKingPos)
		SetKingPos((Team)_players.GetCurrentPlayer(), coords.newPos);
	CorrectArraysOfGivenTeam(oldTile, newTile, replaced.get());
}
void ChessGameRule::CorrectArraysOfGivenTeam(Tile* oldTile, Tile* newTile, GameObject* killed) {
	Team curTeam = (Team)_players.GetCurrentPlayer();
	switch (curTeam)
	{
	case Team::WHITE:
		piecesMainInfo.whiteTiles.erase(std::find(piecesMainInfo.whiteTiles.begin(), piecesMainInfo.whiteTiles.end(), oldTile));
		piecesMainInfo.whiteTiles.push_back(newTile);
		if (killed) {
			piecesMainInfo.blackTiles.erase(std::find(piecesMainInfo.blackTiles.begin(), piecesMainInfo.blackTiles.end(), newTile));
		}
		break;
	case Team::BLACK:
		piecesMainInfo.blackTiles.erase(std::find(piecesMainInfo.blackTiles.begin(), piecesMainInfo.blackTiles.end(), oldTile));
		piecesMainInfo.blackTiles.push_back(newTile);
		if (killed) {
			piecesMainInfo.whiteTiles.erase(std::find(piecesMainInfo.whiteTiles.begin(), piecesMainInfo.whiteTiles.end(), newTile));
		}
		break;
	}
}
void ChessGameRule::PlaceKilledBack(Tile* oldTile, Tile* newTile, GameObject* killed) {
	Team curTeam = (Team)_players.GetCurrentPlayer();
	switch (curTeam)
	{
	case Team::WHITE:
		piecesMainInfo.whiteTiles.erase(std::find(piecesMainInfo.whiteTiles.begin(), piecesMainInfo.whiteTiles.end(), oldTile));
		piecesMainInfo.whiteTiles.push_back(newTile);
		if (killed) {
			piecesMainInfo.blackTiles.push_back(oldTile);
		}
		break;
	case Team::BLACK:
		piecesMainInfo.blackTiles.erase(std::find(piecesMainInfo.blackTiles.begin(), piecesMainInfo.blackTiles.end(), oldTile));
		piecesMainInfo.blackTiles.push_back(newTile);
		if (killed) {
			piecesMainInfo.whiteTiles.push_back(oldTile);
		}
		break;
	}
}
std::list<Tile*>& ChessGameRule::GetWhiteTiles() {
	return piecesMainInfo.whiteTiles;
}
std::list<Tile*>& ChessGameRule::GetBlackTiles() {
	return piecesMainInfo.blackTiles;
}
void ChessGameRule::SetBlackKingPos(sf::Vector2u newPos) {
	piecesMainInfo.blackKingPos = newPos;
}
void ChessGameRule::SetWhiteKingPos(sf::Vector2u newPos) {
	piecesMainInfo.whiteKingPos = newPos;
}
sf::Vector2u ChessGameRule::GetKingPos(Team team) {
	switch (team)
	{
	case Team::WHITE:
		return piecesMainInfo.whiteKingPos;
	case Team::BLACK:
		return piecesMainInfo.blackKingPos;
	default:
		break;
	}
}
void ChessGameRule::SetKingPos(Team team, sf::Vector2u newPos) {
	switch (team)
	{
	case Team::WHITE:
		piecesMainInfo.whiteKingPos = newPos;
		break;
	case Team::BLACK:
		piecesMainInfo.blackKingPos = newPos;
		break;
	default:
		break;
	}
}
sf::Vector2u ChessGameRule::GetStartFieldSize()  {
	return _fieldSize;
};
bool ChessGameRule::CheckGivenTeamForCheckmate(Team team, TilesHolder& holder) {
	switch (team)
	{
	case Team::WHITE:
		return CheckTeamForCheckMate(piecesMainInfo.whiteKingPos, piecesMainInfo.blackTiles, holder);
	case Team::BLACK:
		return CheckTeamForCheckMate(piecesMainInfo.blackKingPos, piecesMainInfo.whiteTiles, holder);
	}
}
void ChessGameRule::Reset(TilesHolder& holder)  {
	CleanBoard(holder);
	_players.Reset();
	ChessFieldGenerator generator;
	piecesMainInfo = generator.PrepareForGame(holder);
	_players.SetPlayerOneGameObjs(&piecesMainInfo.whiteTiles);
	_players.SetPlayerTwoGameObjs(&piecesMainInfo.blackTiles);
}
void ChessGameRule::CleanBoard(TilesHolder& holder) {
	for (unsigned int i = 0; i < 8; i++) {
		for (unsigned int j = 0; j < 8; j++) {
			holder.getTile(sf::Vector2u{ i,j })->DestroyGameObject();
		}
	}
}
bool ChessGameRule::CheckTeamForCheckMate(sf::Vector2u& teamKingPos, std::list<Tile*>& opponentPieces, TilesHolder& holder) {
	for (Tile* elem : opponentPieces) {
		GameObject* enemyPiece = elem->GetGameObject();
		std::list<Tile*> underEnemyAttack;
		enemyPiece->SelectTiles(elem->GetGameCoords(), underEnemyAttack, holder);
		for (Tile* targeted : underEnemyAttack) {
			if (targeted->GetGameCoords() == teamKingPos)
				return true;
		}
	}
	return false;
}