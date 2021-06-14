#pragma once
class HumanPlayer;
#include "Player.h"
#include "Piece.h"
#include "ChessGameRule.h"

class HumanPlayer : public Player {
private:
	std::list<Tile*> selectedTiles;
public:
	HumanPlayer(sf::Color selectColor) : Player(selectColor) {};
	void SetControllableObjects(std::list<Tile*>* objects) override;
	std::optional<MoveCoords> HandleClick(sf::Vector2i mouseCoords, TilesHolder& holder, std::list<Tile*>* opponentControlledObjects) override;
	void SelectTiles(sf::Vector2i mouseCoords, TilesHolder& holder, std::list<Tile*>& opponentControlledObjects);
	void PaintSelected();
	std::optional<sf::Vector2u> MakeTurn(sf::Vector2i mouseCoords, TilesHolder& holder, std::list<Tile*>& opponentControlledObjects);
	void UnSelectTiles();
	std::list<Tile*>* GetControllerObjects() override;
	std::list<Tile*> GetPossibleMoves(TilesHolder& holder) override;
	sf::Color GetColor() override;
	void Reset() override;
};