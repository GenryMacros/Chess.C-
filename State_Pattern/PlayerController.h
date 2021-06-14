#pragma once
#include "Player.h"
#include <memory>
#include <string>

enum class Turns {
	FirstPlayerTurn,
	SecondPlayerTurn
};

class PlayerController {
private:
	std::unique_ptr<Player> _firstPlayer;
	std::unique_ptr<Player> _secondPlayer;
	Turns currentTurn = Turns::FirstPlayerTurn;
public:
	PlayerController(std::unique_ptr<Player> first, std::unique_ptr<Player> second) : _firstPlayer(std::move(first)), _secondPlayer(std::move(second)) {}
	std::optional<MoveCoords> MakeTurn(sf::Vector2i mouseCoord, TilesHolder& holder);
	void SetPlayerTwoGameObjs(std::list<Tile*>* objects);
	void SetPlayerOneGameObjs(std::list<Tile*>* objects);
	std::list<Tile*>* GetCurrentPlayerObjects();
	std::list<Tile*>* GetCurrentPlayerEnemyObjects();
	void PassTurn();
	int GetCurrentPlayer();
	std::list<Tile*> GetCurrentPossibleMoves(TilesHolder& holder);
	std::list<Tile*> GetToCurrentEnemyPossibleMoves(TilesHolder& holder);
	void Reset();
	sf::Color GetPlayerSelectColor(int player);
};