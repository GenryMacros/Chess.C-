#pragma once
class GameObject;
#include "Tile.h"
#include "TilesHolder.h"
#include <list>

class GameObject {
protected:
	Tile* holder;
	sf::Vector2u gamePos;
	sf::Image im;
	sf::Texture tex;
	sf::Sprite sp;
public:
	void Draw(sf::RenderWindow& win)
	{
		win.draw(sp);
	}
	void SetPos(sf::Vector2f pos) {
		sp.setPosition(pos);
	}
	void SetGamePos(sf::Vector2u pos) {
		gamePos = pos;
	}
	virtual void SelectTiles(sf::Vector2u, std::list<Tile*>&, TilesHolder& holder) = 0;
};