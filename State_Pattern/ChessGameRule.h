#pragma once
#include "IGameRule.h"
#include "ChessFieldGenerator.h"
#include <list>
#include <vector>
#include <stdexcept>
#include <limits>
#include "Pawn.h";
#include "Castle.h"
#include "Horse.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "PlayerController.h"
#include "HumanPlayer.h"

class ChessGameRule : public IGameRule {
private:
	const sf::Vector2u _fieldSize = sf::Vector2u(8, 8);
	ChessFieldInfo piecesMainInfo;
	Tile* selectedTile = nullptr;
	PlayerController _players;
	TilesHolder* _holder;
public:
	ChessGameRule();
	virtual void PrepareForGame(TilesHolder& holder) override;
	std::pair<bool, std::string> HandleClick(sf::Vector2i mouseCoords, std::vector<Tile*>& selected, TilesHolder& holder) override;
private:
	bool IsPlayerHaveMoves(sf::Vector2u currentKingPos, TilesHolder& holder);
	bool IsMovePossible(TilesHolder& holder, MoveCoords coords, sf::Vector2u currentKingPos);
	std::unique_ptr<GameObject> ReplacePieceAndReturnKilled(Tile* oldTile, Tile* newTile, sf::Vector2u& currentKingPos);
	void SwapBack(Tile* oldTile, Tile* newTile, sf::Vector2u& currentKingPos, std::unique_ptr<GameObject> killed);
	bool IsPlayerDefeated(TilesHolder& holder, sf::Vector2u currentKingPos);
	bool IsKingAttacked(std::list<Tile*>& tilesUnderAttack, sf::Vector2u currentKingPos);
	void MakeMove(TilesHolder& holder, MoveCoords coords, sf::Vector2u currentKingPos);
	void CorrectArraysOfGivenTeam(Tile* oldTile, Tile* newTile, GameObject* killed);
	void PlaceKilledBack(Tile* oldTile, Tile* newTile, GameObject* killed);
	std::list<Tile*>& GetWhiteTiles();
	std::list<Tile*>& GetBlackTiles();
	void SetBlackKingPos(sf::Vector2u newPos);
	void SetWhiteKingPos(sf::Vector2u newPos);
	sf::Vector2u GetKingPos(Team team);
	void SetKingPos(Team team, sf::Vector2u newPos);
	bool CheckGivenTeamForCheckmate(Team team, TilesHolder& holder);
public:
	virtual sf::Vector2u GetStartFieldSize() override;
	void Reset(TilesHolder& holder) override;
	void CleanBoard(TilesHolder& holder);
private:
	bool CheckTeamForCheckMate(sf::Vector2u& teamKingPos, std::list<Tile*>& opponentPieces, TilesHolder& holder);
};