#pragma once
#include "GameObject.h"
#include "IGameRule.h"
#include <list>
#include <optional>

struct MoveCoords {
	sf::Vector2u oldPos;
	sf::Vector2u newPos;
};

class Player {
protected:
	sf::Color tileSelectColor;
	std::list<Tile*>* _controlledObjects;
	Tile* selectedTile = nullptr;
public:
	Player(sf::Color tileSelect) : tileSelectColor(tileSelect) {};
	virtual std::optional<MoveCoords> HandleClick(sf::Vector2i mouseCoords, TilesHolder& holder, std::list<Tile*>* opponentControlledObjects) = 0;
	virtual void SetControllableObjects(std::list<Tile*>* objects) = 0;
	virtual std::list<Tile*>* GetControllerObjects() = 0;
	virtual std::list<Tile*> GetPossibleMoves(TilesHolder& holder) = 0;
	virtual sf::Color GetColor() = 0;
	virtual void Reset() = 0;
};