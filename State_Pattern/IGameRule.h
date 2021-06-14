#pragma once
#include "TilesHolder.h"

class IGameRule {
public:
	virtual void PrepareForGame(TilesHolder&) = 0;
	virtual std::pair<bool,std::string> HandleClick(sf::Vector2i mouseCoords, std::vector<Tile*>& selected, TilesHolder& holder) = 0;
	virtual sf::Vector2u GetStartFieldSize() = 0;
	virtual void Reset(TilesHolder& holder) = 0;
};